using Firebase;
using Firebase.Auth;
using System.Collections;
using System.Collections.Generic;
using System.Net.NetworkInformation;
using Firebase.Database;
using TMPro;
using UnityEngine;

public class AuthManager : MonoBehaviour
{
    [Header("Firebase")]
    public FirebaseAuth auth; //인증을 관리할 객체
    public FirebaseUser User; //사용자
    public DatabaseReference DBref;

    [Header("Login")]
    public TMP_InputField emailLoginField;
    public TMP_InputField passwordLoginField;
    public TMP_Text warningLoginText;

    [Header("Register")]
    public TMP_InputField emailRegisterField;
    public TMP_InputField userNameRegisterField;
    public TMP_InputField passwordRegisterField;
    public TMP_InputField passwordCheckRegisterField;
    public TMP_Text warningRegisterText;

    public TMP_Text userNameText;
    
    private void Awake()
    {
        Firebase.FirebaseApp.CheckAndFixDependenciesAsync().ContinueWith(task => {
            var dependencyStatus = task.Result;
            if (dependencyStatus == Firebase.DependencyStatus.Available)
            {
                // Create and hold a reference to your FirebaseApp,
                // where app is a Firebase.FirebaseApp property of your application class.
                auth = FirebaseAuth.DefaultInstance;
                DBref = FirebaseDatabase.DefaultInstance.RootReference;

                // Set a flag here to indicate whether Firebase is ready to use by your app.
            }
            else
            {
                UnityEngine.Debug.LogError(System.String.Format(
                  "Could not resolve all Firebase dependencies: {0}", dependencyStatus));
                // Firebase Unity SDK is not safe to use here.
            }
        });
    }

    private IEnumerator Register(string email, string password, string username)
    {
        if(username == "")
        {
            warningRegisterText.text = "Missing Username";
        }
        else if(passwordRegisterField.text != passwordCheckRegisterField.text)
        {
            warningRegisterText.text = "Password does not Match!";
        }
        else
        {
            var task = auth.CreateUserWithEmailAndPasswordAsync(email, password);
            yield return new WaitUntil(() => task.IsCompleted);
            if (task.Exception != null)
            {
                Debug.LogWarning(message: $"Failed to Register:{task.Exception}");
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
                warningRegisterText.text = message;
            }
            else
            {
                User = task.Result.User;
                if(task.Result != null)
                {
                    FirebaseUser user = auth.CurrentUser;
                    if(user != null)
                    {
                        UserProfile profile = new UserProfile
                        {
                            DisplayName = username
                        };
                        var profileTask = user.UpdateUserProfileAsync(profile);
                        yield return new WaitUntil(() => profileTask.IsCompleted);
                        if(profileTask.Exception != null)
                        {
                            Debug.LogWarning(message: $"Failed to Register:{profileTask.Exception}");
                            FirebaseException profileEx = profileTask.Exception.GetBaseException() as FirebaseException;
                            AuthError profileErrorcode = (AuthError)profileEx.ErrorCode;
                            warningRegisterText.text = "Username Set Failed!";
                        }
                        else
                        {
                            //Successfully Register
                            UIManager.Instance.LoginPanel();
                            Debug.Log("User Profile updated Successfully");
                            warningRegisterText.text = "";
                            StartCoroutine(SaveUsername());
                        }
                    }
                }
            }

        }
    }

    public void OnRegister()
    {
        StartCoroutine(Register(emailRegisterField.text, passwordRegisterField.text, userNameRegisterField.text));
    }

    private IEnumerator Login(string email, string password)
    {
        var task = auth.SignInWithEmailAndPasswordAsync(email, password);
        yield return new WaitUntil(() => task.IsCompleted);

        if(task.Exception != null)
        {
            Debug.LogWarning(message: $"Failed to Login:{task.Exception}");
            FirebaseException firebaseEx = task.Exception.GetBaseException() as FirebaseException;
            AuthError errorCode = (AuthError)firebaseEx.ErrorCode;

            string message = "Login Failed!";
            switch (errorCode)
            {
                case AuthError.MissingEmail:
                    message = "Missing Email";
                    break;
                case AuthError.MissingPassword:
                    message = "Missing Password";
                    break;
                case AuthError.WrongPassword:
                    message = "Wrong Password";
                    break;
                case AuthError.InvalidEmail:
                    message = "Invalid Email";
                    break;
                case AuthError.UserNotFound:
                    message = "User Not Found";
                    break;
            }
            warningLoginText.text = message;
        }
        else
        {
            User = task.Result.User;
            Debug.Log($"User signed in Successfully:{User.Email}, {User.UserId}");
            warningLoginText.text = "";

            UIManager.Instance.CloseLogin();
            StartCoroutine(LoadUsername());
        }
    }

    public void OnLogin()
    {
        StartCoroutine(Login(emailLoginField.text, passwordLoginField.text));
    }

    private IEnumerator SaveUsername()
    {
        var DBTask = DBref.Child("users").Child(User.UserId).Child("UserName").SetValueAsync(userNameRegisterField.text);
        yield return new WaitUntil(() => DBTask.IsCompleted);
        if (DBTask.Exception != null)
            Debug.LogWarning($"Save task failed with {DBTask.Exception}");
        else
            Debug.Log("Save Completed");
    }
    
    private IEnumerator LoadUsername()
    {
        var DBTask = DBref.Child("users").Child(User.UserId).Child("UserName").GetValueAsync();
        yield return new WaitUntil(() => DBTask.IsCompleted);
        if (DBTask.Exception != null)
            Debug.LogWarning($"Save task failed with {DBTask.Exception}");
        else
        {
            DataSnapshot snapshot = DBTask.Result;
            Debug.Log("Load Completed");
            userNameText.text = $"UserName: {snapshot.Value}";
        }
    }
}
