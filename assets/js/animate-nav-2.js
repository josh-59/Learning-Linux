$(document).ready(highlight_nav);
$(document).on("scroll", highlight_nav);


function highlight_nav() {

    const screenTop = $(document).scrollTop();
    const screenBottom = screenTop + $(window).height();

    $('#nav_bar_2 a').each( function () {
        const currLink = $(this);
        const refElement = $(currLink.attr("href"));


        if ( refElement.length == 0 ) {
            // Link exists in nav but corresponding div does not exist
            ;
        } else {

            var elemTop = refElement.position().top;
            var elemBottom = elemTop + refElement.height();

            if ( elemTop >= screenTop && elemTop + 100 < screenBottom ) {
                // Can see top
                currLink.addClass("active");
            } else if ( elemTop < screenTop && elemBottom > screenBottom ) {
                // Are in the middle
                currLink.addClass("active");
            } else if ( elemBottom - 10 > screenTop && elemBottom < screenBottom ) {
                // Can see bottom
                currLink.addClass("active");
            } else {
                // Otherwise
                currLink.removeClass("active");
            }
        }
    });
}
