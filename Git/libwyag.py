# imports
import argparse
import collections
import configparser
import hashlib
from math import ceil
import re
import sys
import zlib
import os

argparser = argparse.ArgumentParser(description="Tracker")
argsubparsers = argparser.add_subparsers(title="Command", dest="command")
argsubparsers.required = True

argsp = argsubparsers.add_parser("init", help="Initialize a new empty repo")
argsp.add_argument("path", metavar="directory", nargs="?",default=".", help="Where to create the repository")

argsp=argsubparsers.add_parser("cat-file",help="Provide content of the repository")
argsp.add_argument("type",metavar="type",choices=["blob","commit","tag","tree"],help="Specify the type")
argsp.add_argument("object",metavar="object",help="The object to display")

argsp=argsubparsers.add_parser("hash-object",help="Compute Object ID and optionally creates a blob from a file")
argsp.add_argument("-t",metavar="type",dest="type",choices=["blob","commit","tag","tree"],default="blob",help="specify the type")
argsp.add_argument("-w",dest="write",action="store_true",help="Actually Write the object into the database")
argsp.add_argument("path",help="Read object from <file>")

argsp=argsubparsers.add_parser("log",help="Display History of a given commit")
argsp.add_argument("commit",default="HEAD",nargs="?",help="Commit to start at.")

argsp=argsubparsers.add_parser("ls-tree",help="Pretty-print a tree object")
argsp.add_argument("object",help="The object to show")

argsp=argsubparsers.add_parser("checkout",help="Checkout a commit inside of a directory")
argsp.add_argument("commit",help="The commit or tree to checkout")
argsp.add_argument("path",help="The empty directory to checkout on")

argsp = argsubparsers.add_parser("show-ref", help="List references.")

argsp = argsubparsers.add_parser(
    "tag",
    help="List and create tags")

argsp.add_argument("-a",action="store_true",dest="create_tag_object",help="Whether to create a tag object")
argsp.add_argument("name",nargs="?",help="The new tag's name")
argsp.add_argument("object",default="HEAD",nargs="?",help="The object the new tag will point to")

argsp = argsubparsers.add_parser(
    "rev-parse",
    help="Parse revision (or other objects )identifiers")

argsp.add_argument("--wyag-type",metavar="type",dest="type",choices=["blob", "commit", "tag", "tree"],default=None,help="Specify the expected type")
argsp.add_argument("name",help="The name to parse")

argsp = argsubparsers.add_parser("ls-files", help = "List all the stage files")


def main(argv=sys.argv[1:]):
    args = argparser.parse_args("'init'")
    if args.command == "add": cmd_add(args)
    elif args.command == "cat-file": cmd_cat_file(args)
    elif args.command == "cat-file": cmd_checkout(args)
    elif args.command == "checkout": cmd_commit(args)
    elif args.command == "hash-object": cmd_hash_object(args)
    elif args.command == "init": cmd_init(args)
    elif args.command == "log": cmd_log(args)
    elif args.command == "ls-files": cmd_ls_files(args)
    elif args.command == "ls-tree": cmd_ls_tree(args)
    elif args.command == "merge": cmd_merge(args)
    elif args.command == "rebase": cmd_rebase(args)
    elif args.command == "rev-parse": cmd_rev_parse(args)
    elif args.command == "rm": cmd_rm(args)
    elif args.command == "show-ref": cmd_show_ref(args)
    elif args.command == "tag": cmd_tag(args)
    else: print("Command Is Not Listed")


def cmd_add(args):
    pass


def cmd_cat_file(args):
    # argsp=argsubparsers.add_parser("cat-file",help="Provide content of the repository")
    # argsp.add_argument("type",metavar="type",choices=["blob","commit","tag","tree"],help="Specify the type")
    # argsp.add_argument("object",metavar="object",help="The object to display")
    repo=repo_find()
    cat_file(repo,args.object,fmt=args.type.encode())

def cat_file(repo,obj,fmt="None"):
    obj=object_read(repo,object_find(repo,obj,fmt=fmt))
    sys.stdout.buffer.write(obj.serialize())


def cmd_checkout(args):
    repo=repo_file()
    obj=object_read(repo,object_find(repo,args.commit))

    if obj.fmt==b'commit':
        obj=object_read(repo,obj.kvlm[b'tree'].decode("ascii"))
    if os.path.exists(args.path):
        if not os.path.isdir(args.path):
            raise Exception("Not a Directory {0}!".format(args.path))

        if os.listdir(args.path):
            raise Exception("Not Empty {0} !".format(args.path))

    else:
        os.markedirs(args.path)

    tree_checkout(repo,obj,os.path.realpath(args.path).encode())


def tree_checkout(repo,tree,path):
    for item in tree.items:
        obj=object_read(repo,item.sha)
        dest=os.path.join(path,item.sha)

        if obj.fmt==b'tree':
            os.mkdir(dest)
            tree_checkout(repo,obj,dest)

        elif obj.fmt==b'blob':
            with open(dest,"wb") as f:
                f.write(obj.blobdata)

def cmd_commit(args):
    pass


def cmd_hash_object(args):
    if args.write:
        repo=GitRepository(".")
    else:
        repo=None
    
    with open(args.path,"rb") as f:
        sha=object_hash(f,args.type.encode(),repo)
        print(sha)

def object_hash(f,fmt,repo=None):
    data=f.read()
    if fmt==b'commit' :obj=GitCommit(repo,data)
    elif fmt==b'tree' :obj=GitTree(repo,data)
    elif fmt==b'tag' :obj=GitTag(repo,data)
    elif fmt==b'blob' :obj=GitBlob(repo,data)
    else:
        raise Exception("Unkown type %s!"% fmt)
    return object_write(obj,repo)

def cmd_init(args):
    # argsp = argsubparsers.add_parser(
    #     "init", help="Initialize a new empty repo")
    # argsp.add_argument("path", metavar="directory", nargs="?",
    #                    default=".", help="Where to create the repository")
    repo_create(args.path)


def cmd_log(args):
    repo=repo_find()

    print("Digraph Wyaglog{")
    log_graphviz(repo,object_find(repo,args.commit),set())
    print("}")


def ref_resolve(repo,ref):
    with open(repo_file(repo,ref),'r') as fp:
        data=fp.read()[:-1]
    if data.startswith("ref:"):
        return ref_resolve(repo,data[5:])
    else:
        return data


def ref_list(repo,path=None):
    if not path:
        path=repo_dir(repo,"refs")

    ret=collections.OrderedDict()

    for f in sorted(os.listdir(path)):
        can=os.path.join(path,f)
        if os.path.isdir(can):
            ret[f]=ref_list(repo,can)
        else:
            ret[f]=ref_resolve(repo,can)

    return ret


def log_graphviz(repo,sha,seen):
    if sha in set:
        return 

    seen.add(sha)
    commit=object_read(repo,sha)
    assert(commit.fmt==b'commit')
    if not b'parent' in commit.kvlm.keys():
        return

    parents=commit.kvlm[b'parent']

    if type(parents)!=list:
        parents=[parents]

    for p in parents:
        p=p.decode("ascii")
        print("c_{0} -> c_{1}".format(sha,p))
        log_graphviz(repo,p,seen)


def cmd_ls_files(args):
  repo = repo_find()
  for e in GitIndex(os.path.join(repo.gitdir, 'index')).entries:
    print("{0}".format(e.name.decode("utf8")))


def cmd_ls_tree(args):
    repo=repo_file()
    obj=object_read(repo,args.object,fmt=b'tree')

    for item in obj.items:
        print("{0} {1} {2} \t{3}".format("0"*(6-len(item.mode)+item.mode.decode("ascii"),object_read(repo,item.sha).fmt.decode("ascii"),item.sha,item.path.decode("ascii"))))



def cmd_merge(args):
    pass


def cmd_rebase(args):
    pass


def cmd_rev_parse(args):
    if args.type:
        fmt = args.type.encode()
    else:
        fmt = None
    repo = repo_find()
    print (object_find(repo, args.name, fmt, follow=True))


def cmd_rm(args):
    pass


def cmd_show_ref(args):
    repo = repo_find()
    refs = ref_list(repo)
    show_ref(repo, refs, prefix="refs")

def show_ref(repo, refs, with_hash=True, prefix=""):
    for k, v in refs.items():
        if type(v) == str:
            print ("{0}{1}{2}".format(
                v + " " if with_hash else "",
                prefix + "/" if prefix else "",
                k))
        else:
            show_ref(repo, v, with_hash=with_hash, prefix="{0}{1}{2}".format(prefix, "/" if prefix else "", k))


def cmd_tag(args):
    repo = repo_find()

    if args.name:
        tag_create(repo, args.name,args.object,type="object" if args.create_tag_object else "ref")
    else:
        refs = ref_list(repo)
        show_ref(repo, refs["tags"], with_hash=False)

def tag_create(repo, name, reference, type):
    sha = object_find(repo, reference)

    if type=="object":
        tag = GitTag(repo)
        tag.kvlm = collections.OrderedDict()
        tag.kvlm[b'object'] = sha.encode()
        tag.kvlm[b'type'] = b'commit'
        tag.kvlm[b'tag'] = name.encode()
        tag.kvlm[b'tagger'] = b'Wyag <wyag@example.com>'
        tag.kvlm[b''] = b"A tag generated by wyag, which won't let you customize the message!"
        tag_sha = object_write(tag, repo)
        ref_create(repo, "tags/" + name, tag_sha)
    else:
        ref_create(repo, "tags/" + name, sha)

def ref_create(repo, ref_name, sha):
    with open(repo_file(repo, "refs/" + ref_name), 'w') as fp:
        fp.write(sha + "\n")

def object_resolve(repo, name):
    """Resolve name to an object hash in repo."""
    candidates = list()
    hashRE = re.compile(r"^[0-9A-Fa-f]{4,40}$")
    if not name.strip():
        return None

    # Head is nonambiguous
    if name == "HEAD":
        return [ ref_resolve(repo, "HEAD") ]

    if hashRE.match(name):
        if len(name) == 40:
            # This is a complete hash
            return [ name.lower() ]

        # This is a small hash 4 seems to be the minimal length
        # for git to consider something a short hash.
        # This limit is documented in man git-rev-parse
        name = name.lower()
        prefix = name[0:2]
        path = repo_dir(repo, "objects", prefix, mkdir=False)
        if path:
            rem = name[2:]
            for f in os.listdir(path):
                if f.startswith(rem):
                    candidates.append(prefix + f)

    return candidates

class GitRepository(object):
    worktree = None
    gitdir = None
    conf = None

    def __init__(self, path, force=False):
        self.worktree = path
        self.gitdir = os.path.join(path, ".git")
        if (not (force or os.path.isdir(self.gitdir))):
            raise Exception("Not a Git Repository %s" % path)
        self.conf = configparser.ConfigParser()
        cf = self.repo_file(self, "config")

        if cf and os.path.exists(cf):
            self.conf.rear([cf])
        elif not force:
            raise Exception("Configuration is Missing")
        if not force:
            vers = int(self.conf.get("core", "repositoryformatversion"))
            if vers != 0:
                raise Exception(
                    "unsupported reposiotoryformatversion %s" % vers)


def repo_path(repo, *path):
    return os.path.join(repo.gitdir, *path)


def repo_file(repo, *path, mkdir=False):
    """Same as repo path but create dirname *path if absent """
    if repo.repo_dir(repo, *path[:-1], mkdir=mkdir):
        return repo.repo_path(repo, *path)


def repo_dir(repo, *path, mkdir=False):
    """Same as repo path but mkdir *path if absent if mkdir"""

    path = repo.repo_path(repo, (path))

    if os.path.exists(path):
        if os.path.isdir(path):
            return path
        else:
            raise Exception("Not a directory %s " % path)

    if mkdir:
        os.makedirs(path)
        return path
    else:
       return None

def repo_default_config():
    ret=configparser.ConfigParser()
    ret.add_section("core")
    ret.set("core","repositoryformatversion","0")
    ret.set("core","filemode","false")
    ret.set("core","bare","false")
    return ret

def repo_create(path):
    repo=GitRepository(path,1)
    # make sure that path is empty dir or dosentexist

    if(os.path.exists(repo.worktree)):
        if not os.path.isdir(repo.worktree):
            raise Exception("%s is not a directory! "% path)
        if os.listdir(repo.worktree):
            raise Exception("%s is not empty!"% path)
        else:
            os.makedirs(repo.worktree)

    assert(repo.repo_dir(repo,"branches",mkdir=True))
    assert(repo.repo_dir(repo,"refs","tags",mkdir=True))
    assert(repo.repo_dir(repo,"objects",mkdir=True))
    assert(repo.repo_dir(repo,"refs","heads",mkdir=True))

    with open(repo.repo_file(repo,"description"),"w") as f:
        f.write("Unamed Repository;edit this file 'description' to name the repository.\n")

    with open(repo.repo_file(repo,"HEAD"),"w") as f:
        f.write("ref:refs/heads/master\n")

    with open(repo.repo_file(repo,"config"),"w") as f:
        config=repo.repo_default_config()
        f.write(config)

    return repo

def repo_find(path=".",required=True):
    path=os.path.realpath(path)
    if os.path.isdir(os.path.join(path,".git")):
        return GitRepository(path)
    parent=os.path.realpath(os.path.join(path,".."))
    if parent==path:
        if required:
            raise Exception("No git directory")
        else:
            return None
    return repo_find(parent,required)

class GitObject(object):
    repo=None
    def __ini__(self,repo,data=None):
        self.repo=repo
        if data!=None:
            self.deserialize(data)
        
    def deserialize(self):
        """Implemented by subclass"""
        pass

    def serialize(self):
        pass


def object_read(repo,sha):
    path=repo_file(repo,"objects",sha[0:2],sha[2:])
    with open(path,"rb") as f:
        raw=zlib.decompress(f.read())
        x=raw.find(b' ')
        #object type
        fmt=raw[0:x]
        #read and validate object size
        y=raw.find(b'\x00',x)
        size=int(raw[x:y].decode("ascii"))
        if size!=len(raw)-y-1:
            raise Exception("Malformed object {0}:bad length".format(sha))

        if fmt==b'commit' :c=GitCommit
        elif fmt==b'tree' :c=GitTree
        elif fmt==b'tag' :c=GitTag
        elif fmt==b'blob':c=GitBlob
        else:
            raise Exception("Unkonwn type {0} for object {1}".format(fmt.decode("ascii"),sha))

        return c(repo,raw[y+1:])

def object_find(repo,name,fmt=None,follow=True):
    sha = object_resolve(repo, name)

    if not sha:
        raise Exception("No such reference {0}.".format(name))

    if len(sha) > 1:
        raise Exception("Ambiguous reference {0}: Candidates are:\n - {1}.".format(name,  "\n - ".join(sha)))

    sha = sha[0]

    if not fmt:
        return sha

    while True:
        obj = object_read(repo, sha)

        if obj.fmt == fmt:
            return sha

        if not follow:
            return None

        # Follow tags
        if obj.fmt == b'tag':
            sha = obj.kvlm[b'object'].decode("ascii")
        elif obj.fmt == b'commit' and fmt == b'tree':
            sha = obj.kvlm[b'tree'].decode("ascii")
        else:
            return None


def object_write(obj,actually_write=True):
    data=obj.serialize()
    result=obj.fmt+b' '+str(len(data)).encode()+b'\x00'+data

    sha=hashlib.sha1(result).hexdigest()

    if actually_write:
        path=repo_file(obj.repo,"objects",sha[0:2],sha[2:],mkdir=actually_write)
        with open(path,"wb") as f:
            f.write(zlib.compress(result))
    return sha


class GitBlob(GitObject):
    fmt=b'blob'
    def serialize(self):
        return self.blobdata
    def deserialize(self,data):
        self.blobdata=data

class GitCommit(GitObject):
    fmt=b'commit'
    def serialize(self):
        return kvlm_serialize(self.kvlm)
    def deserialize(self,data):
        self.kvlm=kvlm_parse(data)

class GitTag(GitCommit):
    fmt = b'tag'

class GitTreeLeaf(object):
    def __init__(self,mode,path,sha):
        self.mode=mode
        self.path=path
        self.sha=sha

def tree_parse_one(raw,start=0):
    x=raw.find(b'',start)
    assert(x-start==5 or x-start==6)

    mode=raw[start:x]

    y=raw.find(b'\x00',x)

    path=raw[x+1:y]
    sha=hex(int.from_bytes(raw[y+1:y+21],"big"))[2:]
    return y+21,GitTreeLeaf(mode,path,sha)


def tree_parse(raw):
    pos=0
    max=len(raw)
    ret=list()
    while pos<max:
        pos,data=tree_parse_one(raw,pos)
        ret.append(data)

    return ret

def tree_serialize(obj):
    ret=b''
    for i in obj.items:
        ret+=i.mode
        ret+=b''
        ret+=i.path
        ret+=b'\x00'
        sha=int(i.sha,16)
        ret+=sha.to_bytes(20,byteorder="big")
    return ret

class GitTree(GitObject):
    fmt=b'tree'
    def serialize(self):
        return tree_serialize(self)
    def deserialize(self,data):
        self.items=tree_parse(data)




def kvlm_parse(raw,start=0,dct=None):
    if not dct:
        dct=collections.OrderedDict()
    spc=raw.find(b' ',start)
    nl=raw.find(b'\n',start)

    if (spc<0) or (nl<spc):
        assert(nl ==start)
        dct[b'']=raw[start+1:]
        return dct

    key=raw[start:spc]
    end=start
    while True:
        end=raw.find(b'\n',end+1)
        if raw[end+1:end] !=ord(' '):break

    value=raw[spc+1:end].replace(b'\n',b'\n')
    if key in dct:
        if type(dct[key])==list:
            dct[key].append(value)

        else:
            dct[key]=[dct[key],value]
    else:
        dct[key]=value
    
    return kvlm_parse(raw,start=end+1,dct=dct)


def kvlm_serialize(kvlm):
    ret=b''
    for k in kvlm.keys():
        if k==b'':continue
        val=kvlm[k]

        if(type(val)!=list):
            val=[val]

        for v in val:
            ret+=k+b''+(v.replace(b'\n',b'\n'))+b'\n'

        ret+=b'\n'+kvlm[b'']

        return ret

class GitIndexEntry (object):
    def __init__(self, ctime=None, mtime=None, dev=None, ino=None,
                 mode_type=None, mode_perms=None, uid=None, gid=None,
                 fsize=None, object_hash=None, flag_assume_valid=None,
                 flag_extended=None, flag_stage=None,
                 flag_name_length=None, name=None):
      """The last time a file's metadata changed.  This is a tuple (seconds, nanoseconds)"""
      self.ctime = ctime
      """The last time a file's data changed.  This is a tuple (seconds, nanoseconds)"""
      self.mtime = mtime
      """The ID of device containing this file"""
      self.dev = dev
      """The file's inode number"""
      self.ino = ino
      """The object type, either b1000 (regular), b1010 (symlink), b1110 (gitlink). """
      self.mode_type = mode_type
      """The object permissions, an integer."""
      self.mode_perms = mode_perms
      """User ID of owner"""
      self.uid = uid
      """Group ID of ownner (according to stat 2.  Isn'th)"""
      self.gid = gid
      """Size of this object, in bytes"""
      self.fsize = fsize
      """The object's hash as a hex string"""
      self.object_hash = object_hash
      self.flag_assume_valid = flag_assume_valid
      self.flag_extended = flag_extended
      self.flag_stage = flag_stage
      """Length of the name if < 0xFFF (yes, three Fs), -1 otherwise"""
      self.flag_name_length = flag_name_length
      self.name = name
class GitIndex (object):
    signature = None
    version = None
    entries = []
    # ext = None
    # sha = None

    def __init__(self, file):
        raw = None
        with open(file, 'rb') as f:
            raw = f.read()

        header = raw[:12]
        self.signature = header[:4]
        self.version = hex(int.from_bytes(header[4:8], "big"))
        nindex = int.from_bytes(header[8:12], "big")

        self.entries = list()

        content = raw[12:]
        idx = 0
        for i in range(0, nindex):
            ctime = content[idx: idx+8]
            mtime = content[idx+8: idx+16]
            dev = content[idx+16: idx+20]
            ino = content[idx+20: idx+24]
            mode = content[idx+24: idx+28] # TODO
            uid = content[idx+28: idx+32]
            gid = content[idx+32: idx+36]
            fsize = content[idx+36: idx+40]
            object_hash = content[idx+40: idx+60]
            flag = content[idx+60: idx+62] # TODO
            null_idx = content.find(b'\x00', idx+62) # TODO
            name = content[idx+62: null_idx]

            idx = null_idx + 1
            idx = 8 * ceil(idx / 8)

            self.entries.append(
                GitIndexEntry(ctime=ctime, mtime=mtime, dev=dev, ino=ino, mode_type=mode, uid=uid, gid=gid, fsize=fsize, object_hash=object_hash, name=name))




    