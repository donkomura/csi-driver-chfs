# csi-driver-chfs
The driver allows CO to access CHFS filesystem.
This this a toy implementation of `chfuse` mount.
I recommend to use [meta-fuse-csi-plugin](https://github.com/pfnet-research/meta-fuse-csi-plugin) or [gcs-fuse-csi-driver](https://github.com/GoogleCloudPlatform/gcs-fuse-csi-driver) for production because this implementation has some seccurity issues.

## Usage

We can use Kubernetes (k8s) as CO.

### Start k8s cluster

```
$ minikube start --cpus=4 --memory=8G
$ eval $(minikube -p minikube docker-env)
```

### Build CSI driver image

```
$ docker build . -t chfs-csi-plugin
```

### Build CHFS server image

```
$ docker build server -t chfs-server
```

### Start CHFS server

```
$ docker run -d -it --privileged --name chfsd --cap-add=ALL chfs-server
$ chfsctl start
CHFS_SERVER="ofi+sockets://172.17.0.2:35347"; export CHFS_SERVER;
$ chfsctl status
ofi+sockets://172.17.0.2:35347 ofi+sockets://172.17.0.2: 00000680
chfs          75       1 99 01:25 ?        00:00:46 chfsd -p sockets -s 1073741824 -F 1 -c /tmp/chfs/default-default -S /tmp/server-info-file-chfs
```

### Deploy CSI driver

```
$ cd deploy/chfuse
$ kubectl create -f csi-chfs-driverinfo.yaml
csidriver.storage.k8s.io/chfs.csi.k8s.io created
$ kubectl get csidrivers.storage.k8s.io
NAME              ATTACHREQUIRED   PODINFOONMOUNT   STORAGECAPACITY   TOKENREQUESTS   REQUIRESREPUBLISH   MODES                  AGE
chfs.csi.k8s.io   false            false            false             <unset>         false               Persistent,Ephemeral   7s
$ kubectl create -f csi-chfs-nodeplugin.yaml
daemonset.apps/csi-chfs-nodeplugin created
$ kubectl -n kube-system get pod
NAME                               READY   STATUS    RESTARTS       AGE
coredns-5d78c9869d-vqzvl           1/1     Running   0              3d9h
csi-chfs-nodeplugin-zfr8f          2/2     Running   0              29s
etcd-minikube                      1/1     Running   0              3d9h
kube-apiserver-minikube            1/1     Running   0              3d9h
kube-controller-manager-minikube   1/1     Running   0              3d9h
kube-proxy-fhnwv                   1/1     Running   0              3d9h
kube-scheduler-minikube            1/1     Running   0              3d9h
storage-provisioner                1/1     Running   2 (3d9h ago)   3d9h
```

### Deploy pod

Copy the server address, and fix the following part of `deploy/chfuse/example/app.yaml`.

```
        volumeAttributes:
          server: "ofi+sockets://172.17.0.2:35347" # paste your CHFS server address
```

Then, you can create the `test-app` pod.

```
$ cd deploy/chfuse/example
$ kubectl create -f app.yaml
pod/test-app created
$ kubectl get po
NAME       READY   STATUS    RESTARTS   AGE
test-app   1/1     Running   0          8s
```

You can see if the CHFS is mounted in the pod.

```
$ kubectl exec -it test-app -- /bin/sh
/ # df -T /data
Filesystem           Type       1K-blocks      Used Available Use% Mounted on
chfuse               fuse.chfuse
                                        0         0         0   0% /data
```