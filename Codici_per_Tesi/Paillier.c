#include <stdio.h>
#include "paillier.h"


# Genera chiavi Paillier
public_key, private_key = paillier.generate_paillier_keypair()

print("Chiave pubblica:", public_key)
print("Chiave privata:", private_key)

# Valori delle aziende
azienda1 = 120
azienda2 = 80
azienda3 = 200

# Crittografia (lato aziende)
c1 = public_key.encrypt(azienda1)
c2 = public_key.encrypt(azienda2)
c3 = public_key.encrypt(azienda3)

# Somma cifrata (lato istituto)
c_tot = c1 + c2 + c3

# Decrittazione finale
totale = private_key.decrypt(c_tot)

print("Totale:", totale)
