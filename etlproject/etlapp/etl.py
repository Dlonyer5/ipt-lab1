import pandas as pd
from .models import StudentRaw, StudentClean
import os

def extract_csv():
    base_dir = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
    file_path = os.path.join(base_dir, "students.csv")

    data = pd.read_csv(file_path)

    for _, row in data.iterrows():
        StudentRaw.objects.create(
            student_id=row['id'],
            name=row['name'],
            course=row['course']
        )

def transform_data():
    raw = StudentRaw.objects.all()
    cleaned = []

    for s in raw:
        name = s.name if s.name else "Unknown"
        course = s.course if s.course else "Not Assigned"

        cleaned.append({
            "student_id": s.student_id,
            "full_name": name.title(),
            "course": course.upper()
        })

    return cleaned

def load_data(data):
    for row in data:
        StudentClean.objects.create(
            student_id=row['student_id'],
            full_name=row['full_name'],
            course=row['course']
        )

def run_etl():
    extract_csv()
    cleaned = transform_data()
    load_data(cleaned)