from django.contrib import admin
from .models import StudentRaw, StudentClean

admin.site.register(StudentRaw)
admin.site.register(StudentClean)