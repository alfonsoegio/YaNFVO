nfv("myNfv") {
  openstack("adam") {
    host="88.88.88.88";
    user="user";
    pass="pass";
    tenant_name="project";
    dns="8.8.8.8";
    identity_version=":5000/v3";
    router("myRouter") {
      keypair("myKeypair") {
	nova_generated = 1;
	flavors("myflavors") {
	  image("ubuntu") {
	    url = "https://cloud-images.ubuntu.com/trusty/current/trusty-server-cloudimg-amd64-disk1.img";
	    format = "qcow2";
	    vdu("vdu0") {
	      flavor = myflavors->random();
	      request("myTest") {
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
