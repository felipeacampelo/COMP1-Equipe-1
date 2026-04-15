#Split de páginas com apenas páginas pares
from pypdf import PdfReader, PdfWriter

reader = PdfReader("entrada.pdf")
writer = PdfWriter()

for i, page in enumerate(reader.pages):
    if (i + 1) % 2 == 0:
        writer.add_page(page)

with open("paginas_pares.pdf", "wb") as f:
    writer.write(f)