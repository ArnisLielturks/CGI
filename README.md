Simple CGI script

Besides the nginx you will also need the following packages
```
sudo apt-get install libfcgi-dev
sudo apt-get install spawn-fcgi
```

nginx configuration example
```
events {
  worker_connections 1024;
}

http {
  server {
     listen 80;
    server_name localhost;

    location /cgi {
      fastcgi_pass   127.0.0.1:8000;

      fastcgi_param  GATEWAY_INTERFACE  CGI/1.1;
      fastcgi_param  SERVER_SOFTWARE    nginx;
      fastcgi_param  QUERY_STRING       $query_string;
      fastcgi_param  REQUEST_METHOD     $request_method;
      fastcgi_param  CONTENT_TYPE       $content_type;
      fastcgi_param  CONTENT_LENGTH     $content_length;
      fastcgi_param  SCRIPT_FILENAME    $document_root$fastcgi_script_name;
      fastcgi_param  SCRIPT_NAME        $fastcgi_script_name;
      fastcgi_param  REQUEST_URI        $request_uri;
      fastcgi_param  DOCUMENT_URI       $document_uri;
      fastcgi_param  DOCUMENT_ROOT      $document_root;
      fastcgi_param  SERVER_PROTOCOL    $server_protocol;
      fastcgi_param  REMOTE_ADDR        $remote_addr;
      fastcgi_param  REMOTE_PORT        $remote_port;
      fastcgi_param  SERVER_ADDR        $server_addr;
      fastcgi_param  SERVER_PORT        $server_port;
      fastcgi_param  SERVER_NAME        $server_name;
    }
  }
}
```

To compile script use the following command
```
make
```

To remove compiled files use
```
make clean
```

To start cgi script use following command in the folder where the compiled script is located
```
spawn-fcgi -p 8000 -n main.o
```

To see the script in action open 127.0.0.1/cgi url
