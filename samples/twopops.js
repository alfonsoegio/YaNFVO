nfv("twoPoPs") {
  openstack("dc1") {
    host="88.88.88.88";
    user="user";
    pass="pass";
    tenant_name="project";
    dns="8.8.8.8";
    identity_version=":5000/v3";
    vdu("server1") {
    }
  }
  openstack("dc2") {
    host="88.88.88.88";
    user="user";
    pass="pass";
    tenant_name="project";
    dns="8.8.8.8";
    identity_version=":5000/v3";
    vdu("server2") {
    }
  }
}
