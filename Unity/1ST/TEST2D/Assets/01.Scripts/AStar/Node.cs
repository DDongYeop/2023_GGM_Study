using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Node : IComparable<Node>
{
    // F = G + H 
    public Vector3Int Cellpos;
    public Node Parent;
    public float G; //여태까지 걸어온 경로 
    public float F; //총합 경로

    public int CompareTo(Node other)
    {
        if (other.F == this.F) return 0;
        else
            return other.F < this.F ? -1 : 1;
    }

    public static bool operator == (Node lhs, Node rhs)
    {
        if(lhs is null)
        {
            if (rhs is null)
                return true;
            else
                return false;
        }
        return lhs.Equals(rhs);
    }

    public static bool operator !=(Node lhs, Node rhs) => !(lhs == rhs);

    public bool Equals(Node p)
    {
        if (p is null)
            return false;
        if (this.GetType() != p.GetType())
            return false;
        return Cellpos == p.Cellpos;
    }

    public override bool Equals(object obj) => this.Equals(obj as Node);
    public override int GetHashCode() => Cellpos.GetHashCode();
}
