nfv("twoPoPs") {
  openstack("dc1") {
    host="88.88.88.88";
    username="user";
    password="pass";
    project="project";
    dns="8.8.8.8";
    iversion=":5000/v3";
    image("ubuntu") {
      url = "https://cloud-images.ubuntu.com/trusty/current/trusty-server-cloudimg-amd64-disk1.img";
      format = "qcow2";
      vdu("server1") {
	flavor = "m1.medium";
      }
    }
  }
  openstack("dc2") {
    host="88.88.88.89";
    username="user";
    password="pass";
    project="project";
    dns="8.8.8.8";
    iversion=":5000/v3";
    image("ubuntu") {
      url = "https://cloud-images.ubuntu.com/trusty/current/trusty-server-cloudimg-amd64-disk1.img";
      format = "qcow2";
      vdu("server2") {
	flavor = "m1.medium";
      }
    }
  }
}
