using System.Collections.Generic;
using UnityEngine;

public enum PlayerStateEnum
{
    Idle,
    Move,
    Dash,
    Jump,
    Fall,
    WallSlide,
    WallJump,
    PrimaryAttack
}

public class PlayerStateMachine
{
    public PlayerState CurrentState { get; private set; }
    public Dictionary<PlayerStateEnum, PlayerState> StateDictionary = new();

    private Player _player;

    public void Initalize(PlayerStateEnum startState, Player player)
    {
        _player = player;
        CurrentState = StateDictionary[startState];
        CurrentState.EnterState(); // ���� ���� �־��ְ� ����
    }

    public void ChangeState(PlayerStateEnum newState)
    {
        CurrentState.ExitState();
        CurrentState = StateDictionary[newState];
        CurrentState.EnterState();
    }

    public void AddState(PlayerStateEnum state, PlayerState playerState)
    {
        StateDictionary.Add(state, playerState);
    }
}
