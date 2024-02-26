## 什么是云原生？

云原生就是一种新的互联网生产模式。相对于传统的互联网软件和产品的产出方式，云原生通过微服务架构，容器技术，容器编排技术以及CI/CD这种能够做到更高效的性能，更方便的测试与持续的部署与交付等等。

## 核心概念

### 集群架构与组件

#### 核心组件

##### 控制面板组件（Master）

- api-server
- controller-manager
- cloud-controller-manager
- scheduler
- etcd

##### 节点组件（Node）

- kubelet
- kube-proxy
- container runtime
  - docker
  - containerd

##### 附加组件

- kube-dns
- ingress controller
- 普罗米修斯
- Dashboard
- Federation
- Fluentd-elasticsearch

#### 服务的分类

- 有状态应用和无状态应用



### 资源和对象

- 资源和对象的关系类似于类与对象的关系

- 可以通过配置文件yaml/json来描述资源（资源清单）

- 一切皆资源

#### 资源的分类

##### 元数据级

- Horizontal Pod Autoscaler(HPA) 
- PodTemplate
- LimitRange

##### 集群级

- Namespace
- Node
- ClusterRole
- ClusterRoleBinding

##### 命名空间级

###### 工作负载型

- Pod  // 可以理解成容器组
  - 副本(replicas) // 完全相同的资源实例
  - 控制器 
    - 无状态服务的控制器：ReplicationController(RC) // 动态更新副本数量 , ReplicaSet(RS), Deployment // 滚动升级/回滚，扩缩容，暂停恢复等等
    - 有状态的：StatefulSet // 1. headless service:对dns管理 2. volumeClaimTemplate用于创建卷
    - 守护进程的： DaemonSet  // 为每一个匹配的Node都部署一个后台应用（守护进程）
    - 任务/定时任务：Job, CronJob

###### 服务发现

- Service
- Ingress

###### 存储

- Volume
- CSI

###### 特殊类型配置

- ConfigMap
- Secret
- DownwardAPI

###### 其他

- Role // 定义一组权限 
- RoleBinding



### 对象规约和状态

- 规约(spec)是描述对象实例的期望状态。
- 规约是必备的
- 状态（status）指的是对象的实际状态，由k8s自己维护





























