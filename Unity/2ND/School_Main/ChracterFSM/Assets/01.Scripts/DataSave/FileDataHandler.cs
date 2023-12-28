using System;
using System.IO;
using System.Text;
using UnityEngine;

public class FileDataHandler 
{
    private string _directoryPath = ";";
    private string _filename = "";

    private bool _isEncrypt;
    private bool _isBase64;

    private CryptoModule _cryptoModule;

    public FileDataHandler(string directoryPath, string filename, bool isEncrypt, bool isBase64 = false)
    {
        _directoryPath = directoryPath;
        _filename = filename;
        _isEncrypt = isEncrypt;
        _isBase64 = isBase64;
        
        _cryptoModule = new CryptoModule();
    }

    public void Save(GameData gameData)
    {
        string fullPath = Path.Combine(_directoryPath, _filename); 
        try
        {
            Directory.CreateDirectory(_directoryPath);
            string dataToStore = JsonUtility.ToJson(gameData, true); //인간이 보기 좋게 만들어준다.

            if (_isEncrypt)
            {
                dataToStore = _cryptoModule.AESEncrypt256(dataToStore);
                //dataToStore = EncryptDecryptData(dataToStore);
            }
            /*if (_isBase64)
            {
                dataToStore = Base64Process(dataToStore, false);
            }*/
            
            using(FileStream writeStream = new FileStream(fullPath, FileMode.Create))
            {
                using(StreamWriter writer = new StreamWriter(writeStream))
                {
                    writer.Write(dataToStore);
                }
            }

        }catch(Exception ex)
        {
            Debug.LogError($"Error on trying to save data to file {fullPath}");
        }

    }

    public GameData Load()
    {
        string fullPath = Path.Combine(_directoryPath, _filename);
        GameData loadedData = null;

        if(File.Exists(fullPath))
        {
            try
            {
                string dataToLoad = "";
                using(FileStream readStream = new FileStream(fullPath, FileMode.Open))
                {
                    using(StreamReader reader = new StreamReader(readStream))
                    {
                        dataToLoad = reader.ReadToEnd(); //끝까지 다 읽기
                    }
                }
                
                /*if (_isBase64)
                {
                    dataToLoad = Base64Process(dataToLoad, false);
                }*/
                if (_isEncrypt)
                {
                    dataToLoad = _cryptoModule.Decrypt(dataToLoad);
                    //dataToLoad = EncryptDecryptData(dataToLoad);
                }

                loadedData = JsonUtility.FromJson<GameData>(dataToLoad);
            }catch(Exception ex )
            {
                Debug.LogError($"Error on trying to load data from file {fullPath}");
            }
        }

        return loadedData;

    }

    public void DeleteSaveData()
    {
        string fullPath = Path.Combine(_directoryPath, _filename);

        if (File.Exists(fullPath))
        {
            try
            {
                File.Delete(fullPath);
            }
            catch (Exception e)
            {
                Debug.LogError($"Error on trying to delete file {fullPath}");
            }
        }
    }

    private string _codeWord = "ggmisgreatallthetime";
    private string EncryptDecryptData(string data)
    {
        StringBuilder builder = new StringBuilder();

        for (int i = 0; i < data.Length; ++i)
        {
            builder.Append((char)(data[i] ^ _codeWord[i % _codeWord.Length]));
        }

        return builder.ToString();
    }

    private string Base64Process(string data, bool encoding)
    {
        if (encoding)
        {
            byte[] dataByteArr = Encoding.UTF8.GetBytes(data);
            return Convert.ToBase64String(dataByteArr); //바이트 싹 끄집어와서 6비트로 쪼개고 스트링 조립
        }
        else
        {
            byte[] dataByteArr = Convert.FromBase64String(data);
            return Encoding.UTF8.GetString(dataByteArr);
        }
    }
}
