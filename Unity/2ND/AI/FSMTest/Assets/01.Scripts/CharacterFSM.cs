using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public enum CharacterState
{
    Idle, Move, Jump, Attack
}

public class CharacterFSM : MonoBehaviour
{
    private CharacterState currentState = CharacterState.Idle;
    private CharacterState previousState = CharacterState.Idle;

    private void Update()
    {
        switch (currentState)
        {
            case CharacterState.Idle:
                Debug.Log("Idle");
                break;
            case CharacterState.Move:
                Debug.Log("Moving");
                break;
            case CharacterState.Jump:
                Debug.Log("Jumping");
                break;
            case CharacterState.Attack:
                Debug.Log("Attacking");
                break;
        }
    }

    public void ChangeState(CharacterState newState)
    {
        previousState = currentState;

        if (currentState == CharacterState.Move)
        {
            if (newState == CharacterState.Attack)
            {
                currentState = newState;
                return;
            }
            else if (newState == CharacterState.Jump)
            {
                currentState = newState;
                return;
            }
        }

        if (newState == CharacterState.Attack && previousState != CharacterState.Move)
        {
            Debug.Log("Cannot attack from this state");
            return;
        }

        currentState = newState;
    }
}
