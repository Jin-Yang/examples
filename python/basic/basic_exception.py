#!/usr/bin/python
"This is a module to display how exception works."      # called by module.__doc__


class SimpleError(Exception):
    pass

class MyError(Exception):
    def __init__(self, value):
        self.value = value
    def __str__(self):
        return repr(self.value)


def examples_except():
    '''If the exception or error not catched by any
       code, then the program will exit.'''

    try:  # normal: ACD, except: ABD
        print "This is normal operation."          # A
        #raise TypeError
        #raise IOError, 'Opps, IO error'
        #raise NameError, (2, 'Opps, Name error')
        raise MyError, 8  # OR raise MyError(8)
    except IOError:
        print 'Ooooh, IOError'
        # raise   # reraise the exception, no arguments.
        retval = 'Exception IOError:'              # B
    except TypeError, e:
        print 'Ooooh, TypeError:', e # or e.args[0], e.args[1]
        #print dir(e)
        retval = 'Exception TypeError:', e         # B
    except NameError, (errno, e):
        print 'Ooooh, NameError:', errno, e
        retval = 'Exception IOError:', e           # B
    except MyError, e:
        print 'Ooooh, MyError:', e.value
        retval = 'Exception MyError'               # B
    except (SyntaxError, TypeError):
        print 'Ooooh, SyntaxError/TypeError'
        retval = 'Exception ValueError,TypeError'  # B
    except (KeyError, TypeError), e:
        print 'Ooooh, KeyError/TypeError'
        retval = str(diag) # Maybe e.args[0] and e.args[1] can use.
    except Exception:  # or 'except:', or 'BaseException:' all errors.
        print 'Ooooh, Exception'
        retval = 'some errors cannot identify'
    else:   # This is optional, means there is no error.
        print 'This is also normal operation.'     # C
    finally: # This always execute.
        print 'Normal operation.'                  # D
    # NOTE: if using 'try ... finally ...', when finally block
    #       finished, the exceptions will be reraised.

    import time
    print "\ntest for Ctrl-C"
    try:
        try:
            time.sleep(20)
        except KeyboardInterrupt, e:
            print "inner"
            raise
    except KeyboardInterrupt, e:
        print "outer"

    print
    try:
        assert 1 == 0 , 'One does not equal zero silly!'
    except AssertionError, args:
        print '%s: %s' % (args.__class__.__name__, args)


if __name__ == '__main__': # main function, else module name.
    ret = examples_except()

