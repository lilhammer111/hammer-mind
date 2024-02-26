# Event Basics

**Random Experiment**：

随机试验需满足下面三个特征：

1. 相同条件下，试验行为可重复
2. 试验结果不止一个
3. 试验结果不可预测

随机试验并不是单纯地指某个行为，而是指当我们以某个试验目的，去重复某个行为的过程，因此对于一个完全相同的行为，如果试验目的是不同的，那就是两个试验行为，同时也意味着随机试验除了试验行为外还必须指定试验目的。

> 例如，对于随机试验$E_1$：抛一枚硬币，观察硬币的正反。$E_1$的试验行为就是抛一枚硬币，试验目的是观察硬币的正反。
>
> 又如，对于随机试验$E_2$：抛一枚硬币，观察硬币弹起的次数。$E_2$的试验行为仍然是抛一枚硬币，但是试验目的变成了观察硬币弹起的次数。
>
> 再如，对于试验$e$：抛一枚硬币，观察硬币是否还是硬币。则试验$e$不是一个随机试验，因为无论重复抛多少次硬币，硬币依然是硬币，不满足随机试验必须满足的三个特征中的第二个特征——试验结果不止一个。



**Sample Space:**

一个随机试验$E$中==所有可能的试验结果的集合==，记为 $S = \{r\}$ 。



**Sample point**

一个随机试验的某一次可能的==试验结果==被称为样本点，记为 $r$ ，因此所有样本点的集合也就是样本空间 $S$。

>  如，对于随机试验$E$：抛一次硬币，观察硬币落地不动后，为H（头），还是T（字）“。$E$ 的试验结果（即样本点）可能为以下两种之一：
>
> 1. 硬币落地不动后，T面朝上。记该样本点为 $\text{T}$ 。
> 2. 硬币落地不动后，H面朝上。记该样本点为 $\text{H}$ 。

因此 $E$ 的样本空间 $\Omega = \{\text{H，T}\}$。



**Random Event**

随机事件即样本空间 $S$ 的==子集==，也即试验结果的集合 $\{r_1, r_2,\cdots,r_n\}$，其中 $r_1 \ne r_2 \ne \cdots \ne r_n$，记随机事件为$A$，$B$或$C$，简称事件。

对于一个描述——某某随机事件$A$发生，等价于，该随机试验的结果 $r \in A$。

> 例如，对于某个随机事件$A$，即“掷一次骰子得到奇数点”，记为 $A = \{1, 3, 5\}$。 如果当次随机试验的结果是“掷到点数5”，也即 $r = 5$，则我们认为“事件$A$发生了“，因为随机试验的结果 $r \in A$ 。



**Certain Event:**

对于某一试验，每次试验时，事件 $A$ 都会发生（事件$A$发生，等价于，该随机试验的结果 $r \in A$），则称事件 $A$ 为必然事件。

不难推导 $A = S$ ，$S$ 为样本空间。



**Elementary Event:**

对于事件 $A$，如果 $A$ 只包含一种试验结果，则称 $A$ 为基本事件。



**Impossible Event:**

对于事件 $A$，如果 $A$ 中不包含任何一种试验结果，则称 $A$ 为不可能事件，记为 $\phi$。



**Contain:**

Given events $A$ and $B$ , if event $A$ occurs then event $B$ must occur, $B$ is said to contain $A$ , denoted as $A \subset B$ .



**Union:**

Given events $A$ and $B$ , if either event $A$ or event $B$ occurs, $B$ is said to union $A$ , denoted as $A \cup B$ .



**Intersection:**

Given events $A$ and $B$ , if event $A$ , $B$  occurs at the same time, it said that $A$ intersects $B$ , denoted as $A \cap B$ or $AB$.



The above definitions of union and intersection can be generalized to the situation of more than two events.

we can use $\bigcap\limits_{i=1}^n$ to represents that one of events $A_1, A_2, \cdots, $ and $A_n$ occurs at least and $\bigcup\limits_{i=1}^n$ to represents that all of events occurs at the same time. 



**mutually exclusive:**

If $AB=\phi$, it is said that the event $A$ is mutually exclusive to $B$ . 



**difference:**

If $A-B$, it is said that the event A occurs while the event B doesn't occur.

And the expression $A-B$ is equivalent to the expression $A\cap \overline B$ .



**complementation：**

For any given event $A$ , if there is another events denoted as $\overline A$ can satisfy the equation of $A \cup \overline A = S$ , we call the event $\overline A$ a complementary event.



**commutative law:**

$A \cup B = B \cup A$

$ A \cap B = B \cap A$



**associative law:**

$A\cup(B\cup C)=(A\cup B)\cup C$

$A \cap (B\cap C)=(A\cap B)\cap C$



**distributive law:**

$A\cup(B\cap C)=(A\cup B)\cap (A\cup C)$

$A\cap(B\cup C)=(A\cap B)\cup (A\cap C)$



**De Morgan's laws:**

It refers to a pair of transformation rules in the fields of set theory and Boolean algebra. These laws are used to relate the intersections and unions of sets through complements. Specifically, De Morgan's laws state:

1. The complement of the union of two sets is equal to the intersection of their complements.
2. The complement of the intersection of two sets is equal to the union of their complements.

In mathematical terms, these laws can be expressed as:

1. $\overline {A\cup B}=\overline A \cap \overline B$

2. $\overline {A\cap B}=\overline A \cup \overline B$

, or

1. $(A\cup B)^c=A^c \cap B^c$
2. $(A\cap B)^c=A^c \cup B^c$



**The generalization of De Morgan's laws:**

The generalization of De Morgan's laws extends these principles from two sets to any finite number of sets. In English, this generalization can be stated as follows:

For any finite collection of sets, the complement of the union of all the sets is equal to the intersection of their complements, and the complement of the intersection of all the sets is equal to the union of their complements.

Mathematically, this can be expressed as:

1. $\overline {\bigcap\limits_{i=1}^n A_i} = \bigcup\limits_{i=1}^n \overline {A_i}$
2. $\overline {\bigcup\limits_{i=1}^n A_i} = \bigcap\limits_{i=1}^n \overline {A_i}$

These generalized forms of De Morgan's laws apply to any finite number of sets and are used in various fields such as mathematics, computer science, and logic theory.

  	

**Frequency:**

The definition of frequency is the number of times an event occurs within a specific period or dataset. Mathematically, if an event $A$ occurs $n$ times in a series of trials or observations, the absolute frequency of event $A$ is denoted as $n_A$.

Moreover, the relative frequency of an event $A$ is defined as the ratio of the number of times event $A$ occurs to the total number of trials or observations. If the total number of trials is $n$, which is denoted as $n$ as well,  then the relative frequency of event $A$ denoted as $f_n(A)$ is given by:
$$
f_n(A) = {n_A \over n}
$$


The properties of relative frequency include the following:

1. $0 \leq f_n(A) \leq 1$

2. $f_n(S) = 1$

3. If $A_1,A_2,\cdots,A_k$ are mutually exclusive in pairs, we have: $f_n(\bigcup\limits_{i=1}^kA_i) = \sum\limits_{i=1}^kf_n(A_i)$

   

An important property is:

With the times of the trial increasing, the relative frequency get more stable, the stable value is called $p$.



# Probability Basics

**Probability:**

As we mentioned above, with the times of the trial increasing, the relative frequency get more stable, the stable value is called $p$.

And the $p$ is also called probability denoted as $P(A)=p$, which is the statistical definition of probability.

Let the sample space corresponding to randomized trials be $S$, and for each event $A$, define $P(A)$ that satisfies:

1. nonnegativity: $P(A)\geq0$
2. normality: $P(S) = 1$
3. additivity: $A_iA_j = \phi,i\ne j$, then $P(\bigcup\limits_{i=1}^\infty A_i) = \sum\limits_{i=1}^\infty P(A_i)$.

Then $P(A)$ is said to be the probability of event $A$.



We have the following properties of the probability of event $A$:

1. $P(\phi)=0$

2. $P(A)= 1-P(\overline A)$

3. If $A \subset B$ , then $P(B-A)=P(B)-P(A)$

   **Proof:**

   $\because A\subset B \therefore B=A\cup B$

   $\because A\cup B=(A\cup B)\cap S =(A\cup B)\cap(A\cup \overline A)=A\cup (B\cap\overline A)=A\cup(B-A)$

   $\therefore B = A\cup (B-A)$

    and obviously $A$ and $B-A$ are mutually exclusive.

   Therefore, according to the principle of additivity of probability which states $P(\bigcup\limits_{i=1}^\infty A_i) = \sum\limits_{i=1}^\infty P(A_i)$ 

   $P(B)=P(A\cup(B-A))=P(A)+P(B-A)$ and $P(B) \geq P(A)  \quad \square$

4. Generally, $P(B-A)=P(B)-P(AB)$

   **Proof:**

   $ \because AB \subset B \therefore P(B-AB)=P(B)-P(AB)$ according to the third property of probability

   and $\because B-AB = B\cap \overline {AB}=B\cap (\overline A \cup \overline B)=(B\cap\overline A)\cup(B\cap\overline B)=B\cap\overline A\cup \phi=B\cap\overline A=B-A$

   Therefore, $P(B-AB)=P(B-A)=P(B)-P(AB) \quad \square$

5. Addition formula for probability: $P(A\cup B)=P(A)+P(B)-P(AB)$

   **Proof:**

   $\because A\cup B =A\cup(B-A)$ and $A$ and $B-A$ are mutually exclusive

   $\therefore P(A\cup B )=P(A)+P(B-A)$

   and according to the forth property $P(B-A)=P(B)-P(AB)$

   $\therefore P(A\cup B)=P(A)+P(B-A)=P(A)+P(B)-P(AB) \quad \square$

​	The first generalization of the fifth property:

​	$P(A\cup B\cup C)=P(A)+P(B)+P(C)-P(AB)-P(AC)-P(BC)+P(ABC)$

​	The second generalization of the fifth property:

​	$P(\bigcup\limits_{i=1}^n A_i)=\sum\limits_{i=1}^nP(A_i)-\sum\limits_{1\leq i\leq j \leq n}P(A_iA_j)+\sum\limits_{1\leq i \leq j \leq k \leq n P(A_iA_jA_k)}+\cdots+(-1)^{n-1}P(A_1A_2\cdots A_n)$



**Example:** 

let A and B shoot at the same target, knowing that the prabability of A hitting the target is 0.7, the probability of B hitting the target is 0.6, and the prabability of both hitting the target at the same time is 0.4,

Find: 

(1) the probability that the target is not hit;

(2) the probability that A hits the target while B does not;

Answers:

(1) Let the probability that the target is not hit be $P(\overline A\cap \overline B)$, the probability of A and B hitting the target respectively be $P(A)$ and $P(B)$, and the prabability of both hitting the target at the same time be $P(AB)$ .

so $P(A)=0.7,P(B)=0.6,P(AB)=0.4$ .

we have:

$P(\overline A\cap \overline B)=P(\overline {A\cup B})=1-P(A\cup B)$

According to the addition formula for probability, we have 

$P(A\cup B)=P(A)+P(B)-P(AB)$

$\therefore P(\overline A\cap \overline B)=1-P(A)-P(B)+P(AB)=1-0.7-0.6+0.4=0.1$

(2) Let the probability that A hits the target while B does not be $P(A-B)$

According to the addition formula for probability, we have:

$P(A-B)=P(A)-P(AB)=0.7-0.4=0.3$



# Classic Probability

In short, the classic probability is a model in which each trial outcome(i.e., sample point) occurs with the equal probability in a random trial.

The Classical Probability Model, also known as the classical definition of probability, applies to situations where there are a finite number of equally likely outcomes. Under the classical model, each elementary outcome (i.e., a possible result of the experiment) has the same probability of occurring. This model is based on the principle of equiprobability, meaning if an experiment has $n$ possible outcomes and these outcomes are equally likely, then the probability of each outcome occurring is $\frac 1 n$.

In the classical model, the probability of an event $A$ is calculated using the formula:
$$
P(A)={\text{Number of favorable outcomes to event} A\over \text{Total number of possible outcomes}}
$$

**Example:**

There are 5 balls in a bag, 3 of which are white and 2 of which are yellow, and let the probability of getting each ball be equal.
(1) Take a ball at random from the bag, let $A$ = {take a white ball}, and find $P(A)$;
(2) Take two balls from the bag without putting them back, and let $B$ = {both are white balls}, find $P(B)$;

- [x] **Answers:**

(1) $P(A)=\Large \frac 3 5$

(2) $P(B) = \Large{3\times2\over 5\times4 }={C_3^2 \over C_5^2}=\frac 3 {10}$



Generally, there is $N$ balls in a bag, $a$ of which are white and $b=N-a$ of which are yellow. If we take $n$ balls without putting them back($n \leq N$) and denote that $A_k=\{\text{fetch exactly k white balls}\}\quad (k\leq a)$, then $P(A_k)=\Large{C_a^kC_b^{n-k} \over C_N^n}$, in which $C_N^n=\Large{n \choose k}={N! \over n!(N-n)!}$ .

 

**Example:** 

Assuming that there are a total of 23 people on the soccer field (11 per team, plus one referee), what is the probability that at least two of those 23 people will have the same birthday?

- [x] **Answers:**

Let the probability of birthday in 365 days be equal.

So there are $365^{23}$ possible birthday combinations for 23 people.

For the event $A$ that neither of them has the same birthday, there are $365\times364\times\cdots\times(365-22)$ possible birthday combinations.

So $P(A)=\Large {365\times364\times\cdots\times(365-22) \over 365^{23}}\normalsize \approx0.493$, and then $P(\overline A)=1-P(A)=0.507$ .



**Example:**

There are $a$ white balls and $b$ yellow balls in a bag, which is denoted as $a+b=n$ . Let the probability of taking a ball from the bag be equal. If we repeat the procedure of taking a ball each time without  putting the ball back for $n$ times, find the probability of taking a white ball for the $k$th time.  

- [ ] **Answers:**

considering that we need to take these balls for $n$ times, we can mark the order for each taking from 1 to n. For the first time to take the ball, there is $n$ possibilities because we have $n$ balls. And for the next time, we have $n-1$ possibilities. Therefore, all the possibilities of taking all $n$ balls is $n!$ .

If we'd like to take a white ball for the $k$th time, we need to change our mind when we consider how to take all $n$ balls. 



# Conditional Probability

Conditional probability is a measure of the probability of an event occurring given that another event has already occurred. If the event of interest is A and the event it is conditioned on is B, the conditional probability is written as $P(A|B)$, and is read as "the probability of A given B".

It's defined mathematically as:

$$
P(A|B) = \frac{P(A \cap B)}{P(B)}
$$


provided that $P(B) > 0$ .

Here, 
- $P(A \cap B)$ is the probability that both events A and B occur (also known as the joint probability).
- $P(B)$ is the probability of event B.



The properties of conditional probability are the same as those of common probability:

- $P(B|A)=1-P(\overline B|A)$
- $P(B\cup C|A)=P(B|A)+P(C|A)-P(BC|A)$



The multiplication rule for conditional probability(dependent events) is 
$$
P(A∩B)=P(A)×P(B∣A)
$$
**Example:**

Given $P(A)=\Large{\frac 1 4}$ , $P(B|A)=\Large{\frac 1 3}$ , $P(A|B)=\Large {\frac 1 2}$ , find $P(A\cup B)$, $P(\overline A|A\cup B)$ .

- [ ] **Answer:**

According to the addtion rule for probability, we have:

$P(A\cup B)=P(A)+P(B)-P(AB)$

Addtional, according to the multiplication rule and definition for conditional probability, we have:

$P(AB)=P(A)\times P(B|A)= \frac 1 4 \times \frac 1 3=\frac 1 {12}$

$P(B)=\Large{P(AB) \over P(A|B)}\normalsize=\Large {\frac 1 {12} \over \frac 1 2}\normalsize=\Large\frac 1 6$

$\therefore P(A\cup B)=  \large\frac 1 4  \normalsize+ \large \frac 1 6 \normalsize- \large\frac 1 {12}\normalsize=\large\frac 1 3$





 

















