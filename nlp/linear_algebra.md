# 行列式

n阶行列式：
$$
D=\begin{vmatrix}
a_{11}&a_{12}&\dots &a_{1n}\\
a_{21}&a_{22}&\dots &a_{2n}\\
\vdots&\vdots & \quad &\vdots \\
a_{n1}&a_{n2}&\dots &a_{nn}
\end{vmatrix}
$$
其实这个$D$就是
$$
\sum(-1)^ta_{1p_1}a_{2p_2}\dots a_{np_n}
$$
其中$t$为排列$p_1p_2\dots p_n$的逆序数，总共$n!$项。

# Scalar

标量，就是一个普通的数。

# Vector

向量，一维数组。

# Matrix

矩阵，二维数组。

例如：
$$
\begin{bmatrix}
A_{1,1} & A_{1,2} & A_{1,3} \\
A_{2,1} & A_{2,2} & A_{2,3} \\
A_{3,1} & A_{3,2} & A_{3,3} \\
\end{bmatrix}
$$

# Tensor

张量，简单理解成多维数组吧。

# Transpose

转置。

矩阵最重要的操作。

转置是以对角线为轴作镜像。

从左上角到右下角是**主对角线**(main diagonal)。
$$
(A^T)_{i,j}=A_{j,i}
$$
只要矩阵形状一样，即可相加：
$$
C = A + B
$$

# Broadcasting

广播。

向量与矩阵相加时，需要将向量拓展成矩阵，比如：
$$
a = 
\begin{bmatrix}
1 & 2 & 3
\end{bmatrix}
\Rightarrow
A=\begin{bmatrix}
1 & 2 & 3 \\
1 & 2 & 3 \\
1 & 2 & 3 
\end{bmatrix}
$$
然后再相加。

当我们直接让一个向量 $a$ 与矩阵 $B$ 相加时，也即自动补齐向量 $a$ 的行为，即称为**广播**。

也即：
$$
C=B+a
$$

# Matrix product

矩阵乘法。

如果矩阵$A$的形状是$m\times n$，矩阵$B$的形状是$n\times p$，那结果矩阵$C$的形状就是$m\times p$。

计算方法：

乘积矩阵 $C = AB$ 的每个元素 $c_{ij}$ 由以下方式计算得出：

- 取矩阵 $A$ 的第 $i$ 行和矩阵 $B$ 的第 $j$ 列。
- 将 $A$ 的行元素与 $B$ 的列元素对应相乘，然后将这些乘积求和。

数学上，这可以表示为：
$$
c_{ij}=a_{i1}b_{1j}+a_{i2}b_{2j}+…+a_{in}b_{nj}
$$
其中，$a_{ik}$ 表示矩阵 $A$ 的第 $i$ 行第 $k$ 列的元素，$b_{kj}$ 表示矩阵 $B$ 的第 $k$ 行第 $j$ 列的元素。

特性:

- **不可交换性**：矩阵乘法通常不满足交换律，即 $AB$ 不一定等于 $BA$。
- **结合律**：矩阵乘法满足结合律，即 $(AB)C = A(BC)$。
- **分配律**：矩阵乘法满足分配律，即 $A(B + C) = AB + AC$。

# Dot Product

点乘，也称内积，标量积。

对于向量
$$
a = \begin{bmatrix}
a_1, a_2,...,a_n
\end{bmatrix} \\
b = \begin{bmatrix}
b_1, b_2,...,b_n
\end{bmatrix}
$$
他们的点乘
$$
a\cdot b=a_1b_1+a_2b_2+...+a_nb_n
$$

# Identity Matrix

单位矩阵：任意向量$x$与单位矩阵相乘，都等于向量$x$，则$I_n$为单位矩阵。
$$
\forall x\in \mathbb{R}^{n\times n}, I_nx=x
$$
例如，$I_3$：
$$
\begin{bmatrix}
1& 0& 0 \\
0&1&0\\
0&0&1
\end{bmatrix}
$$

# Matrix Inversion

矩阵逆，记矩阵$A$的矩阵逆为 $A^{-1}$。

则矩阵逆满足：
$$
A^{-1}A = I_n
$$

# 奇异矩阵

如果不能找到一个**方阵**$B$使得$AB=BA=I$，那么**方阵**A为奇异矩阵，反之为**非奇异矩阵**，非奇异矩阵又叫**可逆矩阵**。

行列式为0的**方阵**一定是奇异矩阵。

奇异矩阵的列向量或行向量线性相关。

