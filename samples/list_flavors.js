nfv("myNfv") {
  openstack("adam") {
    host="88.88.88.88";
    username="user";
    password="pass";
    project="project";
    dns="8.8.8.8";
    iversion=":5000/v3";
    network("adam_network") {
      type = "vlan";
      schema = "192.10.10.0/24";
      router("myRouter") {
	keypair("myKeypair") {
	  nova_generated = 1;
	  flavors("myFlavors") {
	    image("ubuntu") {
	      url = "https://cloud-images.ubuntu.com/trusty/current/trusty-server-cloudimg-amd64-disk1.img";
	      format = "qcow2";
	      vdu("vdu0") {
		flavor = myFlavors->random();
		script("test_script") {
		  user = "ubuntu";
		  key = myKeypair->private();
		  source = "./samples/test_script.sh";
		}
	      }
	      event("init") {
		script("test_script") {
		  user = "ubuntu";
		  key = myKeypair->private();
		  source = "./samples/test_script.sh";
		}
	      }
	      request("start") {
		nova_request = "os-start";
	      }
	      request("stop") {
		nova_request = "os-stop";
		script("message") {
		  key = myKeypair->private();
		  script = "#!/bin/env bash\necho 'GOING TO STOP'\n";
		}
	      }
	    }
	  }
	}
      }
    }
  }
}
