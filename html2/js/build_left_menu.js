function initialize_menu() {
    var menu = $("aside");

//    $(menu).load("weather.html");

    menu.append("<p>Содержание:</p><ul class='menu-list'></ul>")
    var menu_list = $("ul.menu-list")

    $(".item-block").each(function(idx, item) {
        var id = "link_item_anchor" + idx;
        $(item).attr("id", id)

        $(menu_list).append(
            "<li class='menu-item'>" +
            "<a href='" + "#" + id + "'>" +
            "<p>" + item.getAttribute("summary") + "</p>" +
            "</a>" +
            "</li>"
        )
    });
}


function initialize_header() {
    $("header").load("header.html");
}


function initialize_footer() {
    $("footer").load("footer.html");
}


function init_all() {
    initialize_header();
//    initialize_menu();
    initialize_footer();
}

$(document).ready(init_all);
