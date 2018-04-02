(function(exports) {
    exports.skip = 0;
})(this.events = {});

function getContent(fragmentId, callback){
    const request = new XMLHttpRequest();

    request.onload = function () {
        callback(request.responseText);
    };

    request.open("GET", fragmentId + ".html");
    request.send(null);
}

//work with pages
function navigate(){
    const fragmentId = location.hash.substr(1);
    getContent(fragmentId, function (content) {
        document.getElementById("cur").innerHTML = content;
        let user = localStorage.getItem("user");
        checkUser(user);
        if(fragmentId === "photos"){
            startWork();
        }
        if(fragmentId === "add"){
            document.getElementsByClassName("input-upload-photos")[0].addEventListener("keydown", function () {
                if(event.keyCode === 32 || event.keyCode === 0) {
                    setTimeout(function(){document.forms['addForm']['tags-upload'].value += "#"}, 10);
                }
            });
            document.getElementsByClassName("input-upload-photos")[0].addEventListener("focus", function () {
                if(document.forms['addForm']['tags-upload'].value === "")
                    document.forms['addForm']['tags-upload'].value = "#";
            });
            document.getElementById("cancel").addEventListener("click", function () {
                if(confirm("Do you want to leave this page?")) {
                    location.hash = "#photos";
                    navigate();
                }
            })
        }
    });
}


if(!location.hash) {
    location.hash = "#photos";
}

navigate();

window.addEventListener("hashchange", navigate);

function startWork() {
    let user = localStorage.getItem("user");
    checkUser(user);
    showPosts(0, 10, "StartPosts");

    if(user !== null) {
        menu(document.getElementsByClassName("photos")[0]);
        document.getElementById("logout").addEventListener("click", logout);
    }
    else
        document.getElementById("login").addEventListener("click", function () {
            location.hash = "#login";
            navigate();
        });
}

function logout() {
    localStorage.removeItem("user");
    checkUser(localStorage.getItem("user"));
    location.hash = "#photos";
    navigate();
}

function loginSubmit() {
    let username = document.forms['login']['user'].value;
    localStorage.setItem("user", username);
    localStorage.removeItem("StartPosts");
    location.hash = "#photos";
    navigate();
}

function filterForm() {
    let date = document.forms['filter']['date'].value;
    let author = document.forms['filter']['name'].value;
    let hashs = document.forms['filter']['hashTags'].value.split(" ");
    let foundPosts = JSON.parse(localStorage.getItem("StartPosts"));

    if(date !== "")
        foundPosts = foundPosts.filter(post => (new Date(post.createdAt) <= Date.now()));
    if(author !== "")
        foundPosts = foundPosts.filter(post => post.author === author);
    if(!hashs.every(item => item === ""))
        for(let i = 0; i < hashs.length; i++)
            foundPosts = foundPosts.filter(post => post.hashTags.indexOf(hashs[i]) !== -1);

    localStorage.setItem("foundPosts", JSON.stringify(foundPosts));
    localStorage.setItem("filters", JSON.stringify(date + "," + author + "," + hashs));
    showPosts(0,10, "foundPosts");
}

function fillTags(elem) {
    elem.value = elem.value.concat(" #");
}

function addPost() {
    let user = localStorage.getItem("user");

    let descr = document.forms['addForm']['description-upload'].value;
    let tags = document.forms['addForm']['tags-upload'].value.split(" ");

    let post = {};
    post.id = parseInt(localStorage.getItem("id")) + 1;
    localStorage.setItem("id", post.id);
    post.author = user;
    post.createdAt = new Date(Date.now());
    post.description = descr;
    post.hashTags = tags;
    post.likes = [];
    post.photoLink = 'https://pp.userapi.com/c824501/v824501399/d7c57/YUvjj-ydbHk.jpg';

    if(!modulePost.addPhotoPost(JSON.parse(localStorage.getItem("StartPosts")), post, "StartPosts"))
    {
        alert('Some fields are not filled!');
    }
    else {
        localStorage.removeItem("adding");
        modulePost.addPhotoPost(JSON.parse(localStorage.getItem("AllPosts")), post, "AllPosts");
        location.hash = "#photos";
        navigate();
    }
}

function loadPosts() {
    showPosts(events.skip, 10, "StartPosts");

    if (modulePost.amount <= 0) {
        this.removeEventListener("click", loadPosts);
        this.style.display = 'none';
    }
}


    //likes
function makeLike(elem, id, author) {
    let savedPosts = JSON.parse(localStorage.getItem("StartPosts"));
    let post = modulePost.getPhotoPost(savedPosts, id);
    let likes = elem.parentNode;
    let index = post.likes.indexOf(author);
    let icon = "";

    if (index === -1) {
        post.likes.push(author);
        icon = "fa fa-heart";
    }
    else {
        post.likes.splice(index, 1);
        icon = "fa fa-heart-o";
    }

    modulePost.editPhotoPost(savedPosts, id, post);
    localStorage.setItem("StartPosts", JSON.stringify(savedPosts));

    likes.firstChild.innerHTML = post.likes.length;
    likes.children[1].className = icon;
    sizeLike(likes.children[1], index);
}

function sizeLike(like, isOn) {
    if (isOn === -1)
        like.style.fontSize = 25 + 'px';
    else
        like.style.fontSize = 15 + 'px';

    setTimeout(function () {
        like.style.fontSize = 20 + 'px';
    }, 400);
}

function menu(elem) {
    let savedPosts = JSON.parse(localStorage.getItem("StartPosts"));

    elem.addEventListener("click", function (e) {
        let target = e.target || e.srcElement;
        let id = target.getAttribute('id');

        if (id.startsWith("like"))
            makeLike(target, id.replace('like', ''), "Veronika");
        if (id.startsWith("delete"))
            removePost(target, savedPosts, id.replace('delete', ''));

    });
}



