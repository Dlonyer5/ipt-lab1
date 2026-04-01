from django.shortcuts import render, redirect
from .etl import run_etl

def upload_and_run(request):
    if request.method == "POST":
        file = request.FILES.get('csvfile')

        if file:
            with open("students.csv", "wb+") as f:
                for chunk in file.chunks():
                    f.write(chunk)

            run_etl()

        return render(request, "etlapp/upload.html")

    return render(request, "etlapp/upload.html")