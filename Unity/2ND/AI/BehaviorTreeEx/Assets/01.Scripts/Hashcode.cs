using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Hashcode : MonoBehaviour
{
    public string PlayerName { get; set; }
    public int PlayerScore { get; set; }

    public override int GetHashCode()
    {
        return PlayerName.GetHashCode() ^ PlayerScore.GetHashCode();
    }

    public override bool Equals(object obj)
    {
        if (obj == null || GetType() != obj.GetType())
            return false;

        Hashcode otherPlayer = (Hashcode)obj;
        return PlayerName == otherPlayer.PlayerName && PlayerScore == otherPlayer.PlayerScore;
    }
}
