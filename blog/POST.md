======================================
NFV Descriptors, an alternative view
======================================
------------------------------------------------------------------------------------------
Introducción
------------------------------------------------------------------------------------------

El paradigma NFV (Network Function Virtualisation)
recogido en las especificaciones de la
ETSI (https://docbox.etsi.org/ISG/NFV/Open/Publications_pdf/Specs-Reports)
tiene como objetivo establecer las lineas maestras
sobre las que construir y ofertar una nueva familia
de servicios por parte de las operadoras de telecomunicaciones y
desarrolladores de servicios y aplicaciones a los clientes
ya sean usuarios particulares, empresas y/o entes gubernamentales.

Las características principales del nuevo ecosistema pasan por:

- Virtualización:
Facilitando la independencia con respecto
del hardware que sustenta redes y aplicaciones permitiendo
a su vez una mejora de la flexibilidad de las soluciones.

- Multitenencia:
Explotando la virtualización permitir a
distintos operadores trabajar sobre la misma infraestructura
física y/o lógica particionada de acuerdo a contrato,
especificaciones de rendimiento, seguridad, etc ...

- Modularidad:
Debe existir la posibilidad de componer
los servicios desarrollados para ofrecer servicios "compuestos"
de modo que un operador pueda ofertar una determinada composición
de funcionalidades provistas por los desarrolladores de servicios
(por ejemplo una compañía podría contratar un servicio de proxy
además de un firewall trabajando conjuntamente para proteger
sus redes además de controlar el acceso a contenidos por parte
de sus trabajadores).

- Servicios centrados en el cliente:
La implementación mediante
software de las funciones de red implicadas permite a su vez
ganar una mayor granularidad con respecto al ajuste individualizado
de las características del servicio, así como permitir una
trazabilidad precisa en cuanto a calidad del servicio, facturación, etc ...

- Automatización y ubicuidad:
Al tratarse de funciones virtualizadas
puede programarse su despliegue automatizado en distintos tipos de infraestructura
ya sean centros de datos próximos a nodos de red y/o por ejemplo
pequeñas infraestructuras cercanas a los bordes de la red como se explora
en el proyecto Sesame (Small cEllS coordinAtion for Multi-tenancy and Edge services).

En resumen, el escenario soñado es el de construir un mercado de aplicaciones
como Google Play o la Apple Store para operadores de telecomunicaciones.


------------------------------------------------------------------------------------------
Arquitectura e implementación
------------------------------------------------------------------------------------------

Existen en la actualidad muchas iniciativas tratando de adherirse a las
especificaciones de la ETSI respecto al paradigma NFV, proyectos de diversa
índole tratando de implementar casos de uso y demostraciones todos ellos compartiendo
un núcleo común denominado el orquestador de funciones NFV.

Mi experiencia particular pasa por el desarrollo y soporte de uno de esos orquestadores
llamado TeNOR, además de la prospección con respecto de Open Source Mano y creo que ambos
adolecen de la misma problemáticas:

- Sobre-especificación:
El estándar de la ETSI sugiere propouestas para
la arquitectura del orquestador y eso no es buena idea
del mismo modo que no lo sería que
el W3C definiese la arquitectura de un hipotético navegador idealizado ... de lo único
que se ha de preocupar el desarrollador del navegador es de soportar las funcionalidades
especificadas por el W3C y de acuerdo a ello elegir el tipo de arquitectura a su antojo.

- El martillo y los clavos:
Todo son microservicios, añadámosle contenedores, si es posible anidados
y ensamblemos el conjunto completo con interficies REST mal documentadas
intercambiando intrincadísimos descriptores y registros JSON y/o YAML que implicarán
toneladas de código ad-hoc con objecto de soportar las complejas lógicas de negocio
en base a tan rudimentarias formas de representación; por no hablar de la persistencia
que en el mejor de los casos pasará por un ORM que mapeará a una BBDD SQL y en el peor
a una flamante instancia de MongoDB (porque escala dicen ...).

- La GUI:
Cualquier orquestador NFV que se precie debe contar además con una
GUI sobrecargada de formularios gigantescos que permitan añadir la capa de confusión
necesaria para conseguir hacer del producto algo tan incomprensible que
sea difícil poder evaluar las deficiencias de la implementación.

Por todo ello todas las iniciativas para implementar soluciones de orquestación
NFV pasan por construir catálogos y conversores de descriptores a plantillas de despliegue
utilizando diversos gestores de infraestrutura computacional como Openstack, AWS, Azure,
a nivel de red como Opendaylight, etc ... y añadir una capa de gestión de eventos
y configuraciones a desencadenar bajo determinadas circunstancias (por ejemplo escalado
ante una caída de la calidad del servicio) o bajo demanda del propio operador (como
podría ser el caso de operaciones de mantenimiento, backup o actualización).

------------------------------------------------------------------------------------------
Una visión alternativa
------------------------------------------------------------------------------------------

Tratando de pensar en una solución totalmente distinta a la habitual
basada en la idea de dotar de mayor inteligencia a los descriptores dotándolos
de algo más de inteligencia elevándolos a la categoría de pequeños programas
escritos en una sintaxis que soporte la noción de ámbito; por ejemplo si pretendemos
desplegar una máquina virtual en determinado centro de datos deberemos anidarla
en una sección de nuestro descriptor que contenga la información relativa
a dicho centro de datos, por ejemplo:

```
  openstack("dc1") {
    host="88.88.88.88";
    username="user";
    password="pass";
    project="project";
    dns="8.8.8.8";
    version=":5000/v3";
    image("ubuntu") {
      url = "https://images.ubuntu.com/cloudimg-amd64.img";
      format = "qcow2";
      vdu("server1") {
	flavor = "m1.medium";
	network_id = "f60874ea-059e-11e8-9c34-00e04c680ef3";
      }
    }
  }
```
En este caso, el compilador NFV verificaría que puede acceder
a las APIs de Openstack al recorrer el árbol sintáctico, una vez validado
ya tendría acceso a la API de Glance para dar de alta una nueva imagen
de máquina virtual Ubuntu y a partir de ella crear una instancia
de servidor con la capacidad m1.medium y con un puerto a una red
pre-existente. Si en el mismo descriptor al mismo nivel anidáramos
otra estructura similar en un segundo centro de datso dc2 obtendríamos
de forma automática el soporte para múltiples centros de datos.
(ver https://github.com/alfonsoegio/YaNFVO/blob/master/samples/twopops.js)

Todo esto en lo que se referiría al aprovisionamiento de recursos
inicial, el soporte del ciclo de vida de dichos recursos requeriría
de una API a generar y desplegar tras la compilación del servicio
cuya descripción podría estar soportada por una seria de referencias
a scripts, claves privadas, acciones concretas a realizar sobre los servicios
y siempre teniendo en consideración el ámbito de sus declaraciones
dentro de la jerarquía del descriptor, por ejemplo:

```
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
```

de https://github.com/alfonsoegio/YaNFVO/blob/master/samples/list_flavors.js

Consistiría en dar de alta un centro de datos, crear una red usando la interfaz
de Neutron, enlazar esa red con la pública gracias a un router virtual,
generar una clave privada usando la API de Nova, dar de alta
una imagen y desplegarla con un flavor aleatorio; sobre ella definir
varios eventos a ejecutar bajo distintas condiciones.

------------------------------------------------------------------------------------------
Estado actual de la implementación
------------------------------------------------------------------------------------------

Actualmente hay un parser generado con Bison-Flex además de estructuras
para soportar la interpretación de los recursos así como una taba de símbolos
asociada que permita la separación de ámbitos de interpretación.
