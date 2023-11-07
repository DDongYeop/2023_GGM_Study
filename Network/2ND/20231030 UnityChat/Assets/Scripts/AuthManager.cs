using System;
using System.Collections;
using System.Collections.Generic;
using Firebase;
using Firebase.Auth;
using TMPro;
using UnityEngine;

public class AuthManager : MonoBehaviour
{
    [Header("Firebase")] 
    public FirebaseAuth Auth; //인증을 관리할 객체
    public FirebaseUser User; //사용자

    [Header("Login")] 
    public TMP_InputField EmailLoginField;
    public TMP_InputField PasswordLoginField;
    public TMP_Text WarningLoginText;
    
    [Header("Register")]
    public TMP_InputField EmailRegisterField;
    public TMP_InputField UserNameRegisterField;
    public TMP_InputField PasswordRegisterField;
    public TMP_InputField PasswordCheckRegisterField;
    public TMP_Text WarningRegisterText;
    
    private void Awake()
    {
        Firebase.FirebaseApp.CheckAndFixDependenciesAsync().ContinueWith(task => {
            var dependencyStatus = task.Result;
            if (dependencyStatus == Firebase.DependencyStatus.Available) {
                // Create and hold a reference to your FirebaseApp,
                // where app is a Firebase.FirebaseApp property of your application class.
                Auth = FirebaseAuth.DefaultInstance;

                // Set a flag here to indicate whether Firebase is ready to use by your app.
            } else {
                UnityEngine.Debug.LogError(System.String.Format(
                    "Could not resolve all Firebase dependencies: {0}", dependencyStatus));
                // Firebase Unity SDK is not safe to use here.
            }
        });
    }

    private IEnumerator Register(string email, string password, string username)
    {
        if (username == "")
        {
            WarningRegisterText.text = "Missing Username";
        }
        else if (PasswordRegisterField.text != PasswordCheckRegisterField.text)
        {
            WarningRegisterText.text = "Password does not Mathf";
        }
        else
        {
            var task = Auth.CreateUserWithEmailAndPasswordAsync(email, password);
            yield return new WaitUntil(() => task.IsCompleted);

            if (task.Exception != null)
            {
                UnityEngine.Debug.LogWarning(message: $"Failed to Register:{task.Exception}");
                FirebaseException firebaseEx = task.Exception.GetBaseException() as FirebaseException;
                AuthError errorCode = (AuthError)firebaseEx.ErrorCode;

                string message = "Register Failed!";
                switch (errorCode)
                {
                    case AuthError.MissingEmail:
                        message = "Missing Email";
                        break;
                    case AuthError.MissingPassword:
                        message = "Missing Password";
                        break;
                    case AuthError.WeakPassword:
                        message = "Weak Password";
                        break;
                    case AuthError.EmailAlreadyInUse:
                        message = "Email Already In Use";
                        break;
                }

                WarningRegisterText.text = message;
            }
            else
            {
                if (task.Result != null)
                {
                    FirebaseUser user = Auth.CurrentUser;
                    if (user != null)
                    {
                        UserProfile profile = new UserProfile
                        {
                            DisplayName = username
                        };
                        var profileTask = user.UpdateUserProfileAsync(profile);
                        yield return new WaitUntil(() => profileTask.IsCompleted);
                        if (profileTask.Exception != null)
                        {
                            Debug.LogWarning(message:$"Fail to Register:{profileTask.Exception}");
                            FirebaseException profileEx = profileTask.Exception.GetBaseException() as FirebaseException;
                            AuthError profileErrorcode = (AuthError)profileEx.ErrorCode;
                            WarningRegisterText.text = "Username Set Failed!";
                        }
                        else
                        {
                            //Successfully Register
                            UIManager.Instance.LoginPanel();
                            Debug.Log("User Profile Updated Successfully");
                            WarningRegisterText.text = "";
                        }
                    }
                }
            }
        }
    }

    public void OnRegister()
    {
        StartCoroutine(Register(EmailRegisterField.text, PasswordRegisterField.text, UserNameRegisterField.text));
    }
}
