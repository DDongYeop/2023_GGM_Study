using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using UnityEngine;

public class SaveManager : MonoSingleton<SaveManager>
{
    [SerializeField] private string filename;
    private GameData _gameData;
    private List<ISaveManager> _saveManagerList;
    private FileDataHandler _fileDataHandler;

    [SerializeField] private bool _isEncrypt;
    [SerializeField] private bool _isBase64;

    private void Start()
    {
        _fileDataHandler = new FileDataHandler(Application.persistentDataPath, filename, _isEncrypt, _isBase64);
        _saveManagerList = FindAllSaveManagers();
        
        LoadGame();
    }

    public void NewGame()
    {
        _gameData = new GameData();
    }

    public void LoadGame()
    {
        _gameData = _fileDataHandler.Load();
        if (_gameData == null)
        {
            Debug.Log("No save data found");
            NewGame();
        }

        foreach (var saveManager in _saveManagerList)
        {
            saveManager.LoadData(_gameData);
        }
    }

    public void SaveGame()
    {
        foreach (var saveManager in _saveManagerList)
        {
            saveManager.SaveData(ref _gameData);
        }
        
        _fileDataHandler.Save(_gameData);
    }

    private List<ISaveManager> FindAllSaveManagers()
    {
        return FindObjectsOfType<MonoBehaviour>(true).OfType<ISaveManager>().ToList();
    }

    [ContextMenu("Delete save file")]
    public void DeletSaveData()
    {
        //이따
        _fileDataHandler = new FileDataHandler(Application.persistentDataPath, filename, _isEncrypt, _isBase64);
        _fileDataHandler.DeleteSaveData();
    }

    private void OnApplicationQuit()
    {
        SaveGame();
    }
}
