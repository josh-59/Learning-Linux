$(document).ready(function () {
  var screenTop = $(document).scrollTop();
  var screenBottom = screenTop + $(window).height();

  console.log(screenTop);

  $('#nav_bar_2 a').each(function () {
      var currLink = $(this);
      var refElement = $(currLink.attr("href"));

      var elemTop = refElement.position().top;
      var elemBottom = elemTop + refElement.height();

      if ( elemTop >= screenTop && elemTop + 100 < screenBottom ) { // Can see top
        currLink.addClass("active");
      } else if ( elemTop < screenTop && elemBottom > screenBottom ) { // Are in the middle
        currLink.addClass("active");
      } else if ( elemBottom - 10 > screenTop && elemBottom < screenBottom ) { // Can see bottom
        currLink.addClass("active");
      } else {
          currLink.removeClass("active");
      }
  });
});

$(document).on("scroll", function() {
    var screenTop = $(document).scrollTop();
    var screenBottom = screenTop + $(window).height();

    console.log(screenTop);

    $('#nav_bar_2 a').each(function () {
        var currLink = $(this);
        var refElement = $(currLink.attr("href"));

        var elemTop = refElement.position().top;
        var elemBottom = elemTop + refElement.height();

        // Note:  .class="content" div's have top padding of 50px.
        if ( elemTop >= screenTop && elemTop + 100 < screenBottom ) { // Can see top
          currLink.addClass("active");
        } else if ( elemTop < screenTop && elemBottom > screenBottom ) { // Are in the middle
          currLink.addClass("active");
        } else if ( elemBottom - 10 > screenTop && elemBottom < screenBottom ) { // Can see bottom
          currLink.addClass("active");
        } else {
            currLink.removeClass("active");
        }
    });
});
