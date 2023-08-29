using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class HashcodeResult : MonoBehaviour
{
    private void Start()
    {
        Hashcode player1 = new GameObject("Player1").AddComponent<Hashcode>();
        player1.PlayerName = "Alice";
        player1.PlayerScore = 100;

        //Hashcode player2 = player1;
        Hashcode player2 = new GameObject("Player2").AddComponent<Hashcode>();
        player2.PlayerName = "Alice";
        player2.PlayerScore = 200;

        bool equalsResult = player1.Equals(player2);
        int hashCode1 = player1.GetHashCode();
        int hashCode2 = player2.GetHashCode();

        Debug.Log($"Equals Result: {equalsResult}");
        Debug.Log($"HashCode of Player1: {hashCode1}");
        Debug.Log($"HashCode of Player2: {hashCode2}");
    }
}
