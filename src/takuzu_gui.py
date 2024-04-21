import tkinter as tk

class affichage_grille:
	def __init__(self, master, lignes=2, colonnes=2):
		self.master = master
		self.lignes = lignes
		self.colonnes = colonnes
		self.frame = tk.Frame(self.master)
		self.reset_all()

	def clicker(self, i, j):
		bouton = self.boutons[i][j]
		if bouton["text"] == " ":
			bouton["text"] = "0"
		elif bouton["text"] == "0":
			bouton["text"] = "1"
		else:
			bouton["text"] = " "

	def recuperer_grille(self):
		grille = []
		for row in self.boutons:
			grille_row = []
			for bouton in row:
				grille_row.append(bouton["text"])
			grille.append(grille_row)
		return grille

	def envoie(self):
		self.grille = self.recuperer_grille()
		with open('grille.txt', 'w') as f:
			f.write(str(self.lignes) + '\n')
			for row in self.grille:
				f.write(''.join('#' if cell == ' ' else cell for cell in row) + '\n') #'vide' if cell == ' ' else cell for cell in row
		root.quit()
	
	def plus(self):
		if self.lignes < 16:
			self.lignes += 2
			self.colonnes += 2
			self.reset_all()
	
	def moins(self):
		if self.lignes > 2:
			self.lignes -= 2
			self.colonnes -= 2
			self.reset_all()
	
	def afficher_grille(self):
		self.boutons = []
		for i in range(self.lignes):
			row = []
			for j in range(self.colonnes):
				bouton = tk.Button(self.frame, text=" ", width=2, command=lambda i=i, j=j: self.clicker(i, j))
				bouton.grid(row=i, column=j)
				row.append(bouton)
			self.boutons.append(row)
	
	def reset_all(self):
		self.frame.destroy()
		self.frame = tk.Frame(self.master)
		self.frame.pack()
		self.afficher_grille()
		
		self.moins_bouton = tk.Button(self.frame, text="-", command=self.moins)
		self.moins_bouton.grid(row=self.lignes, column=0, columnspan=1)
		
		self.envoie_bouton = tk.Button(self.frame, text="envoie", command=self.envoie)
		self.envoie_bouton.grid(row=self.lignes, column=1, columnspan=2)
		
		self.plus_bouton = tk.Button(self.frame, text="+", command=self.plus)
		self.plus_bouton.grid(row=self.lignes, column=3, columnspan=1)

root = tk.Tk()
grid = affichage_grille(root)
root.mainloop()
