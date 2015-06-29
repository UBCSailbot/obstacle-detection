class logWrite:
	log = None

	def new(self, vid_name):
		self.log = open(vid_name + '.label', 'w+')

	def write(self):
		pass

	def close(self):
		self.log.close()