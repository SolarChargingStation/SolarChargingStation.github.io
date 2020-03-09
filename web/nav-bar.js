$(function () {
  var bar = '';
bar += '<ul class="navbar-nav mr-auto">';
// index.html
bar += '<li id="index" class="nav-item">';
bar += '<a class="nav-link" href="/SolarChargingStation.github.io/web/index.html">Home</a>';
bar += '</li>';
// about.html
bar += '<li id="about" class="nav-item">';
bar += '<a class="nav-link" href="/SolarChargingStation.github.io/web/about.html">About Us</a>';
bar += '</li>';
//// dropdown (tech)
bar += '<li class="nav-item dropdown">';
bar += '<a class="nav-link dropdown-toggle" id="navbarDropdownMenuLink" data-toggle="dropdown" aria-haspopup="true" aria-expanded="false">Tech Used</a>';
bar += '<div class="dropdown-menu dropdown-primary" aria-labelledby="navbarDropdownMenuLink">';
bar += '<a id="SolarPanel" class="dropdown-item" href="/SolarChargingStation.github.io/web/techUsed/SolarPanel.html">Solar Panels</a>';
bar += '<a id="micro" class="dropdown-item" href="/SolarChargingStation.github.io/web/techUsed/micro.html">Computers & Microcontrollers</a>';
bar += '<a id="RFID" class="dropdown-item" href="/SolarChargingStation.github.io/web/techUsed/RFID.html">RFID</a>';
bar += '<a id="motors" class="dropdown-item" href="/SolarChargingStation.github.io/web/techUsed/motors.html">Motors</a>';
bar += '</div>';
bar += '</li>';
// \dropdown
// blog
bar += '<li class="nav-item">';
bar += '<a id="blog" class="nav-link" href="/SolarChargingStation.github.io/web/blog/blog_oct.html">Team Blog</a>';
bar += '</li>';
// docs.html
bar += '<li class="nav-item">';
bar += '<a id="docs" class="nav-link" href="/SolarChargingStation.github.io/web/docs.html">Documents</a>';
bar += '</li>';
// sustainability.html
bar += '<li class="nav-item">';
bar += '<a id="sustainability" class="nav-link" href="/SolarChargingStation.github.io/web/sustainability.html">Sustainability</a>';
bar += '</li>';
// operation.html
bar += '<li class="nav-item">';
bar += '<a id="operation" class="nav-link" href="/SolarChargingStation.github.io/web/operation.html">Operation</a>';
bar += '</li>';
// sources.html
bar += '<li class="nav-item">';
bar += '<a id="sources" class="nav-link" href="/SolarChargingStation.github.io/web/sources.html">Sources</a>';
bar += '</li>';
// end of navbar
bar += '</ul>';

  $("#main-bar").html(bar);

  var id = getValueByName("id");
  $("#" + id).addClass("active");
});

function getValueByName(name) {
  var url = document.getElementById('nav-bar').getAttribute('src');
  var param = new Array();
  if (url.indexOf("?") != -1) {
    var source = url.split("?")[1];
    items = source.split("&");
    for (var i = 0; i < items.length; i++) {
      var item = items[i];
      var parameters = item.split("=");
      if (parameters[0] == "id") {
        return parameters[1];
      }
    }
  }
}