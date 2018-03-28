(function(exports) {
    events.skip = 0;
    let top = 10;

    //loading posts
    function loadPosts() {
        showPosts(events.skip, top, "StartPosts");
        events.delete();
        events.likes();
        if(modulePost.amount <= 0) {
            this.removeEventListener("click", loadPosts);
            this.style.display = 'none';
        }
    }


    //likes
    function makeLike(i, id, author) {
        let savedPosts = JSON.parse(localStorage.getItem("StartPosts"));
        let post = modulePost.getPhotoPost(savedPosts, id);
        let likes = document.getElementsByClassName("post-likes")[i];
        let index = post.likes.indexOf(author);
        let icon = "";

        if (index === -1) {
            post.likes.push(author);
            icon = "fa fa-heart";
        }
        else{
            post.likes.splice(index, 1);
            icon = "fa fa-heart-o";
        }

        modulePost.editPhotoPost(savedPosts, id, post);
        localStorage.setItem("StartPosts", JSON.stringify(savedPosts));

        likes.firstChild.innerHTML = post.likes.length;
        likes.children[1].className = icon;
        sizeLike(likes.children[1]);
    }

    function sizeLike(like) {
        like.style.fontSize = 25 + 'px';
        setTimeout(function () {
            like.style.fontSize = 20 + 'px';
        }, 400);
    }

    //filter posts

    checkUser("Nik Reid");
    showPosts(0, 10, "StartPosts");

    //loading posts
    let loadButton = document.getElementById("load");
    if(modulePost.amount > 0) {
        loadButton.addEventListener("click", loadPosts);
        loadButton.style.display = 'block';
    }
    else
        loadButton.style.display = 'none';


    //likes
    exports.likes = function () {
        let savedPosts = JSON.parse(localStorage.getItem("StartPosts"));
        let likeButtons = [];
        for (let i = 0; i < savedPosts.length; i++) {
            let buttonLike = document.getElementById("like" + savedPosts[i].id);
            likeButtons.push(buttonLike);
        }

        for (let i = 0; i < likeButtons.length; i++) {
            likeButtons[i].addEventListener("click", function () {
                makeLike(i, savedPosts[i].id, "Veronika");
            });
        }
    };

    //delete post
    exports.delete = function deletes() {
        let deleteButtons = [];
        let amountOfEditButtons = document.getElementsByClassName("edit").length;
        for (let i = 0; i < amountOfEditButtons; i++) {
            let deleteButton = document.getElementsByClassName("edit")[i].children[1];
            deleteButtons.push(deleteButton);
        }

        for (let i = 0; i < deleteButtons.length; i++) {
            let id = deleteButtons[i].id.replace('delete', '');
            deleteButtons[i].addEventListener("click", function () {
                removePost(JSON.parse(localStorage.getItem("StartPosts")).findIndex(post => post.id === id), JSON.parse(localStorage.getItem("StartPosts")), id);
            });
        }
    };
    events.delete();
    events.likes();

    //filter posts

})(this.events = {});
