==========================================================================================
NFV Descriptors, an alternative view
==========================================================================================

------------------------------------------------------------------------------------------
Introducción
------------------------------------------------------------------------------------------

El paradigma NFV (Network Function Virtualization)
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
El estándar de la ETSI define la arquitectura del orquestador y eso no es buena idea
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

Por todo ello todas las iniciativas para implementar soluciones de orquestación
NFV pasan por construir catálogos y conversores de descriptores a plantillas de despliegue
utilizando diversos gestores de infraestrutura computacional como Openstack, AWS, Azure,
a nivel de red como Opendaylight, etc ... y añadir una capa de gestión de eventos
y configuraciones a desencadenar bajo determinadas circunstancias (por ejemplo escalado
ante una caída de la calidad del servicio) o bajo demanda del propio operador (como
podría ser el caso de operaciones de mantenimiento, backup o actualización).





