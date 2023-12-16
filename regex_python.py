import re

sentence='start with a beautiful smile endi\n hell'
pattern=re.compile(r'\b.{4}\b$',re.MULTILINE)
matches=pattern.finditer(sentence)
for match in matches:
    print(match)
    

text = "this is is python application programming class"

pattern = 'is'

# print([i.span() for i in re.finditer(pattern,text)])

matched_obj  = re.compile(pattern)

# print(matched_obj.search(text))

print(re.sub(pattern,"Akshar",string="hello is is is is is is is is is ",count=0))

s = 'this is python . class'
match = re.search('^th.s',s)
# print(match)