using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using Random = UnityEngine.Random;

public class SoundEffect : MonoBehaviour
{
    private AudioSource _audioSource;
    private float _basePitch;

    private void Awake()
    {
        _audioSource = GetComponent<AudioSource>();
        _basePitch = _audioSource.pitch;
    }

    public void PlayClip(AudioClip clip, float pitchRandom = 0)
    {
        _audioSource.pitch = _basePitch + pitchRandom == 0 ? 0 : Random.Range(-pitchRandom, pitchRandom);
        _audioSource.clip = clip;
        _audioSource.Play();

        StartCoroutine(DestroyCoroutine(clip.length + 0.2f));
    }

    private IEnumerator DestroyCoroutine(float time)
    {
        yield return new WaitForSeconds(time);
        _audioSource.Stop();
        
        Destroy(gameObject);
    }
}
