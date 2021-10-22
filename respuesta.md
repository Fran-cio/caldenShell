# Respuesta
No fue tan facil encontrar informacion al respecto, ya que revise el libro e hice busquedas puntuales y solamente encontraba cosas del pipe aplicandose y como usarlo.
Hasta que revise el archivo **Filesystem**:

``` bash 
❯ cat filesystems
nodev	sysfs
nodev	tmpfs
nodev	bdev
nodev	proc
nodev	cgroup
nodev	cgroup2
nodev	cpuset
nodev	devtmpfs
nodev	configfs
nodev	debugfs
nodev	tracefs
nodev	securityfs
nodev	sockfs
nodev	bpf
nodev	pipefs  <---
nodev	ramfs
nodev	hugetlbfs
nodev	devpts
	ext3
	ext2
	ext4
	squashfs
	vfat
nodev	ecryptfs
	fuseblk
nodev	fuse
nodev	fusectl
nodev	efivarfs
nodev	mqueue
nodev	pstore
nodev	autofs
nodev	binfmt_misc
nodev	overlay
nodev	aufs
```
Buscando un poco mas, ahora con un concepto especifico, di con el siguiente [Link](https://www.quora.com/What-is-the-use-of-%E2%80%9Cpipefs%E2%80%9D-on-Linux-systems "What is the use of “pipefs” on Linux systems?").
El cual cita una pagina que no esta disponible. Pero el, resume algo asi:
> PipeFS es un filesystem virtual unico. Este filesystem es montado en el kernel por lo tanto en el 
> espacio de el usuario.

Como detalle interesante destaca:

> Mientras la mayoria de filesystems son montados en "/", PipeFS se monta en "pipe", haciendo a PipeFS
> si propio root. Este filesystem es un superbloque y no puede exeder ese ancho de sistema.
> El punto de entrada a esta segunda ruta es la system-call "pipe()".

El texto continua explicando la aplicacion de uso y que sin este filesystem los pipes no se pueden hacer. 

La traduccion es de mi autoria asi que puede haber algun error de interpretacion, pero pretende ser una cita textual.
