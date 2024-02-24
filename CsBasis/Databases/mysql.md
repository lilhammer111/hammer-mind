# binlog

mysql server层执行器的操作，无关存储引擎。

使用这个查询语句可以看到binlog存放的位置：

```mysql
show variables like '%bin_log%';
```

结果：

```
mysql> show variables like '%log_bin%';
+---------------------------------+-----------------------------+
| Variable_name                   | Value                       |
+---------------------------------+-----------------------------+
| log_bin                         | ON                          |
| log_bin_basename                | /var/lib/mysql/binlog       |
| log_bin_index                   | /var/lib/mysql/binlog.index |
| log_bin_trust_function_creators | OFF                         |
| log_bin_use_v1_row_events       | OFF                         |
| sql_log_bin                     | ON                          |
+---------------------------------+-----------------------------+
6 rows in set (0.00 sec)
```

进入到`/var/lib/mysql`目录下，使用mysqlbinlog这个工具查看binlog详情：

```mysql
mysqlbinlog --base64-output=decode-rows <binlog_file_name>
```

  



