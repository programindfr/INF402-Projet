import tkinter as tk
from subprocess import run

class affichage_grille:
	def __init__(self, master, lignes=2, colonnes=2):
		self.master = master
		self.lignes = lignes
		self.colonnes = colonnes
		self.frame = tk.Frame(self.master)
		self.reset_all()
		self.confirmation = False

	def clicker(self, i, j):
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
		grille = []
		for row in self.boutons:
			grille_row = []
			for bouton in row:
				grille_row.append(bouton["text"])
			grille.append(grille_row)
		return grille

	def envoie(self):
		if not self.confirmation:
			self.envoie_bouton["text"]= "Confirmer ?"
			self.confirmation = True
		else:
			self.envoie_bouton["text"]= "Calcul..."
			self.master.update()

			self.grille = self.recuperer_grille()
			with open(f'n{self.lignes}.takuzu', 'w') as f:
				f.write(str(self.lignes) + '\n')
				for row in self.grille:
					f.write(''.join('#' if cell == ' ' else cell for cell in row) + '\n')
			run(f"./takuzu n{self.lignes}", shell=True, check=True)
			self.afficher_sol(f'n{self.lignes}_sol.takuzu')

			self.envoie_bouton["text"]="Résultat"
			self.confirmation = False

		
	
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
		
		self.envoie_bouton = tk.Button(self.frame, text="Envoyer", command=self.envoie)
		self.envoie_bouton.grid(row=self.lignes, column=1, columnspan=2)
		
		self.plus_bouton = tk.Button(self.frame, text="+", command=self.plus)
		self.plus_bouton.grid(row=self.lignes, column=3, columnspan=1)




	def afficher_sol(self, f):
		with open(f, 'r') as f:
			lines = f.readlines()
		n = int(lines[0].strip())
		sol = [list(line.strip()) for line in lines[1:]]

		self.lignes = self.colonnes = n
		self.reset_all()

		for i in range(n):
			for j in range(n):
				self.boutons[i][j]["text"] = ' ' if sol[i][j] == '#' else sol[i][j]


root = tk.Tk()
grid = affichage_grille(root)
root.mainloop()
root.quit()
