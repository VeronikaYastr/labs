(function() {
    let skip = 10;
    let top = 10;

    function loadPosts() {
        showPosts(10, top, "StartPosts");
        skip += 10;
        if(skip >= modulePost.amount) {
            buttonLoad.removeEventListener("click", loadPosts);
            buttonLoad.style.display = 'none';
        }
    }

    showPosts(0, 10, "StartPosts");
    let buttonLoad = document.getElementById("load");
    buttonLoad.addEventListener("click", loadPosts);

})();