$(function () {
  var bar = '';
bar += '<ul class="navbar-nav mr-auto">';
// index.html
bar += '<li id="index" class="nav-item">';
bar += '<a class="nav-link" href="index.html">Home</a>';
bar += '</li>';
// about.html
bar += '<li id="about" class="nav-item">';
bar += '<a class="nav-link" href="about.html">About Us</a>';
bar += '</li>';
//// dropdown (tech)
bar += '<li class="nav-item dropdown">';
bar += '<a class="nav-link dropdown-toggle" id="navbarDropdownMenuLink" data-toggle="dropdown" aria-haspopup="true" aria-expanded="false">Tech Used</a>';
bar += '<div class="dropdown-menu dropdown-primary" aria-labelledby="navbarDropdownMenuLink">';
// SolarPanel.html
bar += '<a id="SolarPanel" class="dropdown-item" href="techUsed/SolarPanel.html">Solar Panels</a>';
// micro.html
bar += '<a id="micro" class="dropdown-item" href="techUsed/micro.html">Computers & Microcontrollers</a>';
// RFID.html
bar += '<a id="RFID" class="dropdown-item" href="techUsed/RFID.html">RFID</a>';
// motors.html
bar += '<a id="motors" class="dropdown-item" href="techUsed/motors.html">Motors</a>';
bar += '</div>';
bar += '</li>';
bar += '<li class="nav-item">';
// blog
bar += '<a id="blog" class="nav-link" href="blog/blog_oct.html">Team Blog</a>';
bar += '</li>';
bar += '<li class="nav-item">';
// docs.html
bar += '<a id="docs" class="nav-link" href="docs.html">Documents</a>';
bar += '</li>';
bar += '</ul>';
//bar += '<ul class="navbar-nav ml-auto nav-flelx-icons"><li class="nav-item"><a class="nav-link waves-effect waves-light"href="https://github.com/SolarChargingStation/solarchargingstation.github.io" target="_blank"><i class="fab fa-github"></i></a></li></ul>';
// right side of nav
//bar += '<ul class="navbar-nav ml-auto nav-flelx-icons">';
//bar += '<li class="nav-item">';
//bar += '<a class="nav-link waves-effect waves-light"';
//bar += 'href="https://github.com/SolarChargingStation/solarchargingstation.github.io" target="_blank">';
//bar += '<i class="fab fa-github"></i>';
//bar += '</a>';
//bar += '</li>';
//bar += '</ul>';

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