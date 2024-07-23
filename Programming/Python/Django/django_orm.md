# Django Web框架

## 模型层

### ORM

#### 创建/增加数据

方案一：

利用模型类的`objects`对象，即管理器对象，来实现创建一条数据。

具体语法为`MyModel.objects.create(attr1 = value1, attr2 = value2, ...)`

例如：

```python
from myapp.models import Book

book = Book.objects.create(
    title='The Great Gatsby',
    author='F. Scott Fitzgerald',
    published_date='1925-04-10'
)
```

方案二：

创建`MyModel`的实例对象，并调用`save()`进行保存

具体语法为：

```python
obj = MyModel(attr1 = value1, attr2 = value2)
obj.attr3 = value3
obj.save
```



#### 查询数据

Django ORM中的管理器对象（Manager）提供了多种查询方法，以下是其中的一些：

| function             | description                                                  |
| -------------------- | ------------------------------------------------------------ |
| all()                | 返回全部查询集                                               |
| filter(**kwargs)     | 排除符合指定筛选条件的记录                                   |
| order_by(*fields)    | 根据指定字段对结果进行升序或降序排列。**字段为负则倒序排序** |
| values(*fields)      | 返回一个字典组成的查询集，包含指定字段的值。                 |
| values_list(*fields) | 返回一个元组组成的查询集，包含指定字段的值。                 |
| first()              | 返回第一条记录。                                             |
| last()               | 返回最后一条记录。                                           |
| exists()             | 判断是否存在满足指定条件的记录。                             |
| count()              | 统计满足指定条件的记录数。                                   |

除了以上的方法，还有许多其他的查询方法可以使用。同时，管理器对象也支持链式调用多个查询方法，**前提是返回值是queryset**。例如，`Book.objects.values('title').order_by('-price')`

常用方法及属性：

- `query`属性
  如果拿到一个queryset容器对象，则可以通过QuerySet.query拿到这个queryset的SQL查询语句

  例如，

  ```python	
  # 排序查询
  book = Book.objects.order_by('-price').values('title')
  # 拿到查询语句，即SELECT 'book'.'title' FROM 'book' ORDER_BY 'book'.'price' DESC
  print(book.query)
  ```

- `all()`方法
  语法：`MyModel.objects.all()`
  等同于：`select * from table`
  返回值：QuerySet容器对象(等同于python的列表，只是这个列表里装的是对象)，内部存放MyModel实例
  例子：
  
  ```python
  from bookstore.models import Book
  
  books = Book.objects.all()
  for book in books:
  	print("书名", book.title, "出版社", book.pub)
  ```
  
- `value(column1, column2)`方法
  语法：`MyModel.objects.values(...)`
  等同于：`select column1, column2 from table`
  返回值：QuerySet(但是这个里面放的是**字典**)

- `value_list(column1, column2)`方法
  语法：`MyModel.objects.values(...)`
  等同于：`select column1, column2 from table`
  返回值：QuerySet(但是这个里面放的是**值的元组**)

- `order_by()`
  语法：`MyModel.objects.order_by('-column1', 'column2')`
  等同于：

等值条件查询：

- `filter(条件)`
  语法：`MyModel.objects.filter(attr1 = value1, attr2 = value2)`
  返回值：queryset容器对象，mymodel的实例对象

  说明：逗号默认是and

  例如：

  ```python
  # 查询Author实体中name为王老师并且age等于28的
  author = Author.objects.filter(name='王老师', age=28)
  ```

- `exclude(条件)`
  返回值：不包含此结果的所有数据

- `get(条件)`

  说明：如果结果多于一条或者没有就会报错

非等值的查询：

非等值查询需要利用**查询谓词**。

| 查询谓词     | 描述                            |
| ------------ | ------------------------------- |
| __exact      | 等于，用来筛选等于null的数据    |
| __contains   | 模糊查询，包含                  |
| __startswith | 模糊查询，以xx开始              |
| __endswith   | 模糊查询，以xx结束              |
| __gt         | 大于                            |
| __gte        | 大于等于                        |
| __lt         | 小于                            |
| __lte        | 小于等于                        |
| __in         | in查询，数据是否在指定范围内    |
| __range      | range查询，数据是否在指定区间内 |



例如：

```python
# 等同于 select * from author where id = 1
Author.objects.filter(id__exact=1)
```



#### 修改数据

修改一条数据：

1. 查 `record = MyModel.objects.get(field = value1)`

2. 改 `record.field = value2`

3. 保存`save()`

批量修改数据：

1. 查 `queryset = MyModel.objects.filter(field = value1)`

2. 改 `queryset.update(field =value2)`

注意：update()方法返回值类型是整数，表示更新的条数



#### 删除数据

删除一条数据：

1. 查 `author = Author.objects.get(id=1)`
2. 删 `author.delete()`

删除多条数据：

1. 查 `authors = Author.objects.filter(age__gt=65)`
2. 删 `authors.delete()`

伪删除：

实际在业务中并不会真正地删除数据，而是采用伪删除的方法，即在表中添加一个`is_active`的字段，默认是`True`，执行删除操作的时候将`is_active`字段设置为`False`，例如：

```python
book = Book.objects.get(id=1, is_active=True)
book.is_active = False
book.save()
```

**别忘了`save()`**



#### F对象

当我们需要更新Book实例中所有的零售价涨10元

```python
from django.db.models import F
from bookstore.models import Book
# 这个有点类似于相对处理而不是绝对处理，注意跟上面的修改数据进行比较
Book.objects.all().update(price=F('price')+10)
```



#### Q对象

处理逻辑与&，逻辑或|，逻辑非~等操作。

例如，我们要找出定价低于20元或清华大学出版社的书

```python
from django.db.models import Q
books = Book.objects.filter(Q(price__lt=20)|Q(pub="清华大学出版社"))
```



#### 聚合查询

整表聚合

`Book.objects.aggregate(res=Count('id'))`

分组聚合

先分组

`QuerySet = Book.objects.values('pub')`

后聚合

`QuerySet.annotate(res=Count('id'))`



#### 原生SQL语句

`s1 = Book.objects.raw('select * from bookstore_book where id=%s'%('1 or 1=1'))`



#### 关系映射

##### 一对一

语法：`OneToOneField(类名，on_delete=xxx)`

```python
class A(models.Model):
    ...
class B(models.Model):
    attr = models.OneToOneField(A, on_delete=xxx)
```



级联删除 on_delete

| 值             | 描述                                                         |
| -------------- | ------------------------------------------------------------ |
| models.CASCADE | 一删全删                                                     |
| models.PROTECT | 不都不给删                                                   |
| SET_NULL       | 外键被删了就设置为null,前提是这个字段得能是null，即设定null = True |
| SET_DEFAULT    | 外键被删了，就设置为默认值                                   |

例如：

```python
from django.db import models

class Author(models.Model):
    name = models.CharField(verbose_name="作家", max_length=50)
    
# Wife表有三个字段，一个id，一个name，一个author_id
class Wife(models.Model):
    name = models.CharField(verbose_name="妻子", max_length=50)
    # 一般外键的属性名都规定为类名的小写，即author
    author = models.OneToOneField(Author, on_delete=models.CASCADE)
```

> 如何创建数据？

无外键的创建方式不改变，即

`author1 = Author.objects.create(name='王老师')`，这条数据的id=1

有外键的有两个方案：

1. `wife1 = Wife.objects.create(name='王夫人', author=author1)`

2. `wife1 = Wife.objects.create(name='王夫人', author_id=author1.id)`

如何查询数据？

正向查询：直接通过外键属性查询

通过wife的author属性直接调出author的对象，即`wife.author`，然后再点外键的属性名就能查出来外键的数据，即`wife.author.name`

反向查询：

反向查询类似于正向查询，因为author外键中有个隐藏的wife属性，这个隐藏的属性就是类名的小写



##### 一对多

”多表“上创建外键

语法： `attr = models.ForeignKey(类名，on_delete=xxx)`

