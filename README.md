## Features

### variables
supported variables: boolean, integer, string and lists
```python
>>> x = 123
>>> x
123
>>> y = "abc"
>>> y
"abc"
>>> z = y
>>> z
"abc"
>>> n = True
>>> n
True
>>> list = ["abc,.kdhf", "xyz"]
>>> list
["abc,.kdhf", "xyz"]
```
### Supported operations
  - `type(x)`
  - `len(x)` (only for sequence types)
  - `del x` (delete variable)
 ```python
>>> x = 10
>>> type(x)
<type 'int'>
>>> type(10)
<type 'int'>
>>> del x
>>> x
NameError : name 'x' is not defined
>>> str = "abc"
>>> len(str)
3
```

### Errors (Python-like)
- `SyntaxError`
- `IndentationError`
- `NameError`
- `TypeError`
- 
 ```python
>>> =x
SyntaxError: invalid syntax
>>> x = b
NameError : name 'b' is not defined
>>>    x = 1
IndentationError: unexpected indent
>>> len(x)
TypeError
 ```
