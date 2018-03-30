(function(exports) {
    events.skip = 0;
    let top = 10;

    //loading posts
    function loadPosts() {
        showPosts(events.skip, top, "StartPosts");
        //events.menu(document.getElementsByClassName("photos"));
        if(modulePost.amount <= 0) {
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

    exports.menu = function (elem) {
        let savedPosts = JSON.parse(localStorage.getItem("StartPosts"));

        elem.addEventListener("click", function (e) {
            let target = e.target || e.srcElement;
            let id = target.getAttribute('id');

            if(id.startsWith("like"))
                makeLike(target, id.replace('like', ''), "Veronika");
            if(id.startsWith("delete"))
                removePost(target, savedPosts, id.replace('delete', ''));

        });
    };


    checkUser("Nik Reid");
    showPosts(0, 10, "StartPosts");

    //loading posts
    let loadButton = document.getElementById("load");
    events.menu(document.getElementsByClassName("photos")[0]);
    if(modulePost.amount > 0) {
        loadButton.addEventListener("click", loadPosts);
        loadButton.style.display = 'block';
    }
    else
        loadButton.style.display = 'none';

})(this.events = {});
