# SmartNFVO

SmartNFVO is the NFV smart orchestrator


## Dependencies

- compiler: gcc, flex, bison
- product RESTful APIs: python, flask, requests and ...

## Clone, compile and run first tests

By now, there's only the parser and the tree-building code.

```
git clone https://github.com/alfonsoegio/SmartNFVO.git
cd SmartNFVO
make
./test samples/list_flavors.js
```

Pending things (almost everything), august 2017:

- Resource specs: openstack, router, vdu, vlinks, etc ...
- Symbol table - Scoping Stack
- Python API server generation
- Openstack client libraries integration
- GUI generation as a frontend to generated APIs
- Life-cycle Scripts Templating System (enabling symbol table interpolation)
- Descriptor dynamic conditionals and function call support

## Key idea: Network service compiler

The purpose of this software is to provide
a compiler for a network service descriptor 
in order to build an API specifically devoted
to manage the service provisioning, deployment and
life-cycle events. 

Basic syntax comprises the resource creation following
the basic template rules provided herein:

```
  resource("id1") {
    attribute = 1;
    attribute2 = "value";
      nested_resource("id2") {}
      nested_resource("id3") {
        attribute = id1->function("param");
      }
    }
```

In the example, resource "id1" is going to be provisioned,
executed or deployed
before nested_resources "id2" and "id3" because a parent
resource is by convention a requirement for it's childs;
this way nested_resource "id3" can query it's parent "id1"
once it's created and provisioned about some functional
parameteres. 

For example:

- Multiple PoPs (Openstack)

```
  openstack("myDatacenter") {
    host="88.88.88.88";
    user="user";
    pass="pass";
    tenant_name="project";
    dns="8.8.8.8";
    identity_version=":5000/v3";
  }
```

- Inside an scoped openstack environment: VDU deployment
and bootstrapping

```
      keypair("myKeypair") {
        nova_generated = 1;
	flavors("myFlavors") {
	  image("ubuntu") {
	    url = "https://cloud-images.ubuntu.com/trusty/current/trusty-server-cloudimg-amd64-disk1.img";
	    format = "qcow2";
	    vdu("vdu0") {
	      flavor = myFlavors->random();
	      request("myTest") {
		script("test_script") {
		  user = "ubuntu";
		  key = myKeypair->private();
		  source = "./samples/test_script.sh";
		}
	      }
	    }
	  }
	}
      }

```

Previous example consists on:

-- creating a keypair named myKeypair using openstack's Nova API
-- getting the available flavors from the VIM an naming them as myFlavors
-- creating a new image on Openstack's Glance Service named ubuntu
-- deploying the virtual machine image as a virtual deployment unit vdu0
-- defining some endpoint in the API to be generated called test_script
using the previously generated private key

At the end ideally the compiling, provisioning, deployment and setup
should end with a brand new RESTful API supporting all the operations
defined in the descriptor. 

## What is this about?

During last year I was introduced to a new
paradigm in computer science taking part
in some projects regarding the Network Function
Virtualisation ecosystem mainly based in the
European Telecommunications Standards Institute NFV-standard.

The experience is currently very challenging, but
after many times facing the same problems, the feeling
I have is that the NFV standard it's not production
ready in order to meet the needs of function vendors
and network operators.

The main reason behind the problems faced when
trying to build NFV systems that really work has not
to do with some lack of feature coverage in the standards
neither
the quality of the tools and projects intended to operate
this kind of service management and orchestration systems;
my thoughts about this systems usually have to do with the fact
that maybe we are trying to solve a problem
without the right tools, twisting the approach to meet particular
needs here and there when trying to adapt real systems
to meet the NFV paradigm and perform real stuff at the same time.

### Descriptors, templates and friends

The NFV standard consists of an specification
about how to describe services and it's life-cycle
management. All the approaches to implement systems
dealing with that kind of descriptors rely their
operation on a mix of three features:

- Format translation of static descriptors:
in order to be as agnostic as possible
(translating part of the descriptor as an Openstack
Heat Template (TeNOR) or some input information
for an LXD container host OSM, etc ...)

- Information retrieval:
after conversion and deployment on the Virtualised
Infrastructure Manager (VIM), the NFV-orchestrator
retrieves (usually asynchronously) the information
regarding the provisioned resources like MAC addresses,
IPs, net masks, etc ...

- Lifecycle management:
Either delegating in some middle-ware or not, the NFV-orchestrator
usually executes configuration scripts on the machines using
private keys generated in the VIM or passed by the orchestrator
itself according to operator requests, etc ... 

