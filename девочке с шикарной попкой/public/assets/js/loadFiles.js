function getContent(fragmentId, callback){
  const request = new XMLHttpRequest();

  request.onload = function () {
    callback(request.responseText);
  };

  request.open("GET", fragmentId + ".html");
  request.send(null);
}

function navigate(){
  const fragmentId = location.hash.substr(1);
  getContent(fragmentId, function (content) {
    document.getElementById("cur").innerHTML = content;
  });
}

function loginSubmit() {
  const userName = document.forms["login"]["user"].value;
  userLogIn(userName);
  //location.hash="#content";
  //navigate();
}

if(!location.hash) {
  location.hash = "#add";
}

navigate();

window.addEventListener("hashchange", navigate);
//document.getElementById("login-button").addEventListener("click", loginEvent);