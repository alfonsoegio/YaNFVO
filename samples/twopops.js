nfv("twoPoPs") {
  openstack("dc1") {
    host="88.88.88.88";
    username="user";
    password="pass";
    project="project";
    dns="8.8.8.8";
    iversion=":5000/v3";
    vdu("server1") {
    }
  }
  openstack("dc2") {
    host="88.88.88.88";
    username="user";
    password="pass";
    project="project";
    dns="8.8.8.8";
    iversion=":5000/v3";
    vdu("server2") {
    }
  }
}
