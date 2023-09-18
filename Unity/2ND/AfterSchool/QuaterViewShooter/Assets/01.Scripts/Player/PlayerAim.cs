using UnityEngine;

public class PlayerAim : MonoBehaviour
{
    [Header("���� ����")]
    [SerializeField] private InputReader _inputReader;
    [SerializeField] private Transform _visualTrm;
    [SerializeField] private PlayerAnimator _playerAnimator;
    [SerializeField] private PlayerMovement _playerMovement;

    [Header("���� ��")]
    [SerializeField] private LayerMask _whatIsGround;

    private void LateUpdate()
    {
        Vector2 mousePos = _inputReader.AimPosition;

        Ray ray = CameraManager.MainCam.ScreenPointToRay(mousePos);

        //���⼭ ���ߵ� �ؼ� ���콺 �������� ĳ������ ������� ȸ���ϰ� �ϼ���.
        if(Physics.Raycast(ray, out RaycastHit hitInfo, CameraManager.MainCam.farClipPlane, _whatIsGround))
        {
            Vector3 worldPos = hitInfo.point;
            Vector3 dir = (worldPos - transform.position);
            dir.y = 0;
            _visualTrm.rotation = Quaternion.LookRotation(dir);
        }

        CalulateRotation();
    }

    private void CalulateRotation()
    {
        Vector3 visualDir = Quaternion.Inverse(_visualTrm.rotation) * _playerMovement.MoveVelocity;
        
        _playerAnimator.SetAnimationDirection(new Vector2(visualDir.x, visualDir.z).normalized);
    }
}
