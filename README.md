# csi-driver-chfs
The driver allows Kubernetes to access CHFS filesystem.

## Usage

### Build CSI driver

// cmake

### Build CSI driver image

### Build CHFS server image

### Start CHFS server

```
$ docker run -d -it --privileged --name chfsd range3/chfs chfsd -d -p ofi+sockets
```

spack の場所

```
$ . /home/chfs/.cache/spack/share/spack/setup-env.sh
$ echo $CHFS_SPACK_ENV
/home/chfs/.spack-extension/envs/chfs
```
