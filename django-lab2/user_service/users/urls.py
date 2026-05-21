from django.urls import path
from .views import user_service

urlpatterns = [
    path('', user_service),
]