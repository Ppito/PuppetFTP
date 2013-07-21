
Shadowbox.init({
    modal: true,
    onClose: function(){ window.location.reload(); }
});

$(document).ready(function() {
  $("#notice").css('display', 'none');
  if ($("#notice span")) {
    $("#notice span").each(function(idx, el) {
//      var span = $(el);
//      $.ambiance({message: span.html(), timeout: 5, type: span.attr("class")});

      $(".top-right").notify({
        message: { text: $(el).html() },
	type: $(el).attr("class"),
	fadeOut: { enabled: true, delay: 5000 },
        transition: 'fade'
      }).show();
//        $('.top-right').notify({
//          message: { html: false, text: texte }
//        }).show();
    });
  }

    //    $(".top-right").notify({message:{text:"test"}}).show();


  $("#server div.rightCol div.tabbable ul.nav-tabs li:first-child").addClass("active");

  $("a span").each(function(idx, elem){
      $(elem).parent("a").attr("data-toggle", "tooltip");
      $(elem).parent("a").attr("title", elem.title);
      $(elem).removeAttr("title");
      $(elem).parent("a").tooltip();
  });

});
