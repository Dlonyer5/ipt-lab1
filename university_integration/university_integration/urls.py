from django.contrib import admin
from django.urls import path, include

urlpatterns = [
    path('admin/', admin.site.urls),
    path('api/student/', include('student_app.urls')),
    path('api/library/', include('library_app.urls')),
    path('api/payment/', include('payment_app.urls')),
]