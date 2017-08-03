vnfd("Vcache_i2CAT_1.0") {

  vdu("vcache") {
    controller = 0;
    flavor = "fw-init";
    vm_image("vcache") {
      openstack_id = "4a4d526a-d9d2-478f-bc7d-8ce637740b5f";
    }
    script("bootstrap_script") {
      port = 22;
      shell = "#!/usr/bin/env bash";
      another = 13;
    }
  }

  vdu("vcc") {
    controller = 1;
    flavor = "fw-init";
    vm_image("ubuntu") {
      url = "https://cloud-images.ubuntu.com/trusty/current/trusty-server-cloudimg-amd64-disk1.img";
    }
    script("bootstrap_script") {
      port = 22;
      shell = "#!/usr/bin/env bash";
    }

    connection_point("vl0") {
      /* existing_network = pop_info("network", "name", "provider", "id") ? "provider" : pop_select("network"); */
      alias = "management";
      dhcp = 1;
    }

    connection_point("vl1") {
      alias1 = "data";
      dhcp = 1;
      provider = 1;
      script("add_iface_1") {
	port = 22;
	shell = "#!/usr/bin/env bash";
      }
    }
  }
}
