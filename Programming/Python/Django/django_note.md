## 基础命令

### 查看所有命令

`python3 manage.py help`



### 创建django项目

`django-admin startproject project_name`



### 启动服务器

`python3 manage.py runserver`



## .gitignore

```python
# Byte-compiled / optimized / DLL files
__pycache__/
*.py[cod]
*$py.class

# C extensions
*.so

# Distribution / packaging
.Python
env/
build/
develop-eggs/
dist/
downloads/
eggs/
.eggs/
lib/
lib64/
parts/
sdist/
var/
wheels/
pip-wheel-metadata/
share/python-wheels/
*.egg-info/
.installed.cfg
*.egg

# PyInstaller
#  Usually these files are written by a python script from a template
#  before PyInstaller builds the exe, so as to inject date/other infos into it.
*.manifest
*.spec

# Installer logs
pip-log.txt
pip-delete-this-directory.txt

# Unit test / coverage reports
htmlcov/
.tox/
.nox/
.coverage
.coverage.*
.cache
nosetests.xml
coverage.xml
*,cover
.hypothesis/

# Translations
*.mo
*.pot

# Django stuff:
*.log
local_settings.py
db.sqlite3
media/

# Flask stuff:
instance/
.webassets-cache

# Scrapy stuff:
.scrapy

# Sphinx documentation
docs/_build/

# PyBuilder
target/

# Jupyter Notebook
.ipynb_checkpoints

# IPython
profile_default/
ipython_config.py

# pyenv
.python-version

# pipenv
#   According to pypa/pipenv#598, it is recommended to include Pipfile.lock in version control.
#   However, in case of collaboration, if having platform-specific dependencies or dependencies
#   having no cross-platform support, pipenv may install dependencies that don't work, or not
#   install all needed dependencies.
#Pipfile.lock

# PEP 582; used by e.g. github.com/David-OConnor/pyflow
__pypackages__/

# Celery stuff
celerybeat-schedule
celerybeat.pid

# SageMath parsed files
*.sage.py

# Environments
.env
.venv
env/
venv/
ENV/
env.bak/
python_env_*/
*.serverless/

# ...
media/
.idea/
```





## settings

### 应用

#### 创建应用

`python3 manage.py startapp app_name`

#### 注册应用

在INSTALLED_APPS中添加应用，如

```python
INSTALLED_APPS = [
    'django.contrib.admin',
    'django.contrib.auth',
    'django.contrib.contenttypes',
    'django.contrib.sessions',
    'django.contrib.messages',
    'django.contrib.staticfiles',
    'user'
]
```



### 模板

`'DIRS': [os.path.join(BASE_DIR, 'templates')]`





### MySql数据库

#### 安装mysqlclient

`pip install mysqlclient`

#### 创建数据库

`CREATE  DATABASE  <database_name> CHARACTER SET UTF8;` 

#### 配置settings

```python
DATABASES = {
    'default': {
        'ENGINE': 'django.db.backends.mysql',
        'NAME': 'database_name',
        'USER': 'root',
        'PASSWORD': 'password',
        # 默认主机
        'HOST': '',
        # 默认端口3306
        'PORT': ''
    }
}
```

#### 创建表

...

#### 迁移表

`python3 manage.py makemigrations`

`python3 manage.py migrate`



### Redis数据库

#### 安装pyredis

这里redis就是pyredis

`pip3 install redis`

#### 配置

```python
CACHES = {
    'default': {
        'BACKEND': 'django_redis.cache.RedisCache',
        'LOCATION': 'redis://127.0.0.1:6379/0',
        "OPTIONS": {
            "CLIENT_CLASS": "django_redis.client.DefaultClient",
        },
    },
    'session': {
        'BACKEND': 'django_redis.cache.RedisCache',
        'LOCATION': 'redis://127.0.0.1:6379/1',
        "OPTIONS": {
            "CLIENT_CLASS": "django_redis.client.DefaultClient",
        },
    },
    # 'verify_code': {
    #     'BACKEND': 'django_redis.cache.RedisCache',
    #     'LOCATION': 'redis://127.0.0.1:6379/2',
    #     "OPTIONS": {
    #         "CLIENT_CLASS": "django_redis.client.DefaultClient",
    #     },
    # },
}
```



### 日志输出器

配置

```python
# 日志输出器
BASE_LOG_DIR = Path(__file__).resolve().parent.parent.parent
LOGGING = {
    'version': 1,  # 版本
    'disable_existing_loggers': False,  # 是否禁用已经存在的日志器
    'formatters': {  # 日志信息显示的格式
        'verbose': {
            'format': '%(levelname)s %(asctime)s %(module)s %(lineno)d %(message)s'
        },
        'simple': {
            'format': '%(levelname)s %(module)s %(lineno)d %(message)s'
        },
    },
    'filters': {  # 过滤器
        'require_debug_true': {  # django在debug模式下才输出日志
            '()': 'django.utils.log.RequireDebugTrue',
        },
    },
    'handlers': {  # 日志处理方法
        'console': {  # 向终端中输出日志
            'level': 'INFO',  # 输出等级为“INFO”
            'filters': ['require_debug_true'],
            'class': 'logging.StreamHandler',
            'formatter': 'simple'
        },
        'file': {  # 向文件中输出日志
            'level': 'INFO',  # 输出等级为“INFO”
            'class': 'logging.handlers.RotatingFileHandler',
            'filename': BASE_LOG_DIR / "logs/test_api.log",  # 日志文件的位置
            'maxBytes': 300 * 1024 * 1024,  # 日志文件的大小（300*1024*1024为300MB）
            'backupCount': 10,  # 日志文件的数量（超过设定的最大值会自动备份，备份数量最大值为10）
            'formatter': 'verbose'  # 日志输出格式：使用了在之前定义的'verbose'
        },
    },
    'loggers': {  # 日志器
        'django': {  # 定义了一个名为django的日志器
            'handlers': ['console', 'file'],  # 可以同时向终端与文件中输出日志
            'propagate': True,  # 是否继续传递日志信息
            'level': 'INFO',  # 日志器接收的最低日志级别
        },
    }
}
```



### DRF配置项

配置exceptions.py

```python
# /test_api/utils/excetions.py

from rest_framework.views import exception_handler as drf_exception_handler
import logging
from django.db import DatabaseError
from redis.exceptions import RedisError
from rest_framework.response import Response
from rest_framework import status

# 获取在配置文件中定义的logger，用来记录日志
logger = logging.getLogger('django')


def exception_handler(exc, context):
    """
    自定义异常处理
    :param exc: 异常
    :param context: 抛出异常的上下文
    :return: Response响应对象
    """
    # 调用drf框架原生的异常处理方法
    response = drf_exception_handler(exc, context)

    if response is None:
        view = context['view']
        if isinstance(exc, DatabaseError) or isinstance(exc, RedisError):
            # 数据库异常
            logger.error('[%s] %s' % (view, exc))
            response = Response({'message': '服务器内部错误'}, status=status.HTTP_507_INSUFFICIENT_STORAGE)

    return response
```







```python
# DRF配置项
REST_FRAMEWORK = {
    # 异常处理
    'EXCEPTION_HANDLER': 'test_api.utils.exceptions.exception_handler',
}
```





### 其他配置

```python

LANGUAGE_CODE = 'zh-Hans'

TIME_ZONE = 'Asia/Shanghai'
```



## 模型层

创建的表命名规则为“应用名_表名”