
Shadowbox.init({
    modal: true,
    onClose: function(){ window.location.reload(); }
});

$(document).ready(function() {
  $("#notice").css('display', 'none');
  if ($("#notice span")) {
    $("#notice span").each(function(idx, el) {

      $(".top-right").notify({
        message: { text: $(el).html() },
	type: $(el).attr("class"),
	fadeOut: { enabled: true, delay: 5000 },
        transition: 'fade'
      }).show();
    });
  }


  $("#server div.rightCol div.tabbable ul.nav-tabs li:first-child").addClass("active");

  $("a span").each(function(idx, elem){
      $(elem).parent("a").attr("data-toggle", "tooltip");
      $(elem).parent("a").attr("title", elem.title);
      $(elem).removeAttr("title");
      $(elem).parent("a").tooltip();
  });

  $("#server div.rightCol div.tab-content tr>td span").each(function(idx, elem){
      $(elem).attr("data-toggle", "tooltip");
      $(elem).attr("title", elem.title);
//      $(elem).removeAttr("title");
      $(elem).tooltip();
      $(elem).css("cursor", "help");
  });

});
