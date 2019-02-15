from time import sleep, time

start = time()

sleep(2)

end = str(time() - start).split(".")
print(end)

end = "%s.%ss" % (end[0], end[1][0:4])
print(end)
