import json

class logWrite:
	log = None

	def new(self, vid_name):
		self.log = open(vid_name + '.label', 'w+')

	def write(self, dictionary):
		for key, value in dictionary.items():
			self.log.write(str(key) + " " + json.dumps(value))
			print key, json.dumps(value)

	def close(self):
		self.log.close()