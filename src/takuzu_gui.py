import tkinter as tk
from subprocess import run

class affichage_grille:
	
	# Initialise les attributs de la classe
	# - master : la fenêtre principale
	# - lignes : le nombre de lignes de la grille (par défaut 2)
	# - colonnes : le nombre de colonnes de la grille (par défaut 2)
	def __init__(self, master, lignes=2, colonnes=2):
		self.master = master
		self.lignes = lignes
		self.colonnes = colonnes
		self.frame = tk.Frame(self.master)
		self.sat = " -s"
		self.satState = "on"
		self.reset_all()
		self.confirmation = False
	
	def clicker(self, i, j):
		# La fonction clicker permet de changer l'état d'un bouton lorsqu'on clique dessus
		# paramètres : i, j les coordonnées du bouton
		bouton = self.boutons[i][j]
		if bouton["text"] == " ":
			bouton["text"] = "0"
		elif bouton["text"] == "0":
			bouton["text"] = "1"
		else:
			bouton["text"] = " "
		
		if self.confirmation:
			self.envoie_bouton["text"]= "Envoyer"
			self.confirmation = False
	
	def recuperer_grille(self):
		# La fonction recuperer_grille permet de récupérer la grille actuelle à partir des boutons
		# retourne : la grille sous forme de liste de listes
		grille = []
		for row in self.boutons:
			grille_row = []
			for bouton in row:
				grille_row.append(bouton["text"])
			grille.append(grille_row)
		return grille
	
	def envoie(self):
		# La fonction envoie permet de lancer le calcul du takuzu
		# Si le mode de confirmation n'est pas activé, change le texte du bouton en "Confirmer ?"
		# Sinon, change le texte du bouton en "Calcul..."
		# retourne : le résultat du takuzu
		if not self.confirmation:
			self.envoie_bouton["text"]= "Confirmer ?"
			self.confirmation = True
		else:
			self.envoie_bouton["text"]= "Calcul..."
			self.master.update()

			self.grille = self.recuperer_grille()
			with open(f'dist/n{self.lignes}.takuzu', 'w') as f:
				f.write(str(self.lignes) + '\n')
				for row in self.grille:
					f.write(''.join('#' if cell == ' ' else cell for cell in row) + '\n')
			run(f"./dist/takuzu dist/n{self.lignes}{self.sat}", shell=True, check=True)
			if self.satState == "on":
				self.afficher_sol(f'dist/n{self.lignes}_sol.takuzu')

			self.envoie_bouton["text"]="Résultat"
			self.confirmation = False
	
	def plus(self):
		# Méthode appelée lorsqu'on clique sur le bouton "+"
		if self.lignes < 16:
			self.lignes += 2
			self.colonnes += 2
			self.reset_all()
	
	def moins(self):
		# Méthode appelée lorsqu'on clique sur le bouton "-"
		if self.lignes > 2:
			self.lignes -= 2
			self.colonnes -= 2
			self.reset_all()
	
	def satSwitch(self):
		if self.satState == "on":
			self.sat = ""
			self.satState = "off"
		elif self.satState == "off":
			self.sat = " -s"
			self.satState = "on"
		self.sat_bouton["text"] = f"sat: {self.satState}"
	
	def afficher_grille(self):
		# La fonction afficher_grille permet d'afficher la grille de takuzu
		# La grille est affichée sous forme de boutons
		# retourne : la grille de takuzu
		self.boutons = []
		for i in range(self.lignes):
			row = []
			for j in range(self.colonnes):
				bouton = tk.Button(self.frame, text=" ", width=2, command=lambda i=i, j=j: self.clicker(i, j))
				bouton.grid(row=i, column=j)
				row.append(bouton)
			self.boutons.append(row)
	
	def reset_all(self):
		# La fonction reset_all permet de réinitialiser la grille
		# La grille est détruite et recréée
		# retourne : la grille de takuzu
		self.frame.destroy()
		self.frame = tk.Frame(self.master)
		self.frame.pack()
		self.afficher_grille()
		
		self.moins_bouton = tk.Button(self.frame, text="-", command=self.moins)
		self.moins_bouton.grid(row=self.lignes, column=0, columnspan=1)
		
		self.envoie_bouton = tk.Button(self.frame, text="Envoyer", command=self.envoie)
		self.envoie_bouton.grid(row=self.lignes, column=1, columnspan=2)
		
		self.plus_bouton = tk.Button(self.frame, text="+", command=self.plus)
		self.plus_bouton.grid(row=self.lignes, column=3, columnspan=1)
		
		self.sat_bouton = tk.Button(self.frame, text=f"sat: {self.satState}", command=self.satSwitch)
		self.sat_bouton.grid(row=self.lignes, column=4, columnspan=2)
	
	def afficher_sol(self, f):
		# La fonction afficher_sol permet d'afficher la solution du takuzu
		# paramètres : f le fichier contenant la solution du takuzu
		# La solution est affichée dans la grille
		# retourne : la solution du takuzu
		with open(f, 'r') as f:
			lines = f.readlines()
		n = int(lines[0].strip())
		sol = [list(line.strip()) for line in lines[1:]]

		self.lignes = self.colonnes = n
		self.reset_all()

		for i in range(n):
			for j in range(n):
				self.boutons[i][j]["text"] = ' ' if sol[i][j] == '#' else sol[i][j]

if __name__ == "__main__":
	root = tk.Tk()
	grid = affichage_grille(root)
	root.mainloop()
	root.quit()
